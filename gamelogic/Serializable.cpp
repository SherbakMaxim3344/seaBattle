
#include "Serializable.h"




    Serializable::Serializable(Map* map, ShipManager* shipman, AbilityManager* abilityManager, CoordHolder* coordHolder)
        : map(map), shipman(shipman), abilityManager(abilityManager), coordHolder(coordHolder) {}

    // Метод для вычисления SHA-256 хеша с использованием EVP API
    std::string Serializable::calculateHash(const std::string& input) const {
        EVP_MD_CTX* ctx = EVP_MD_CTX_new(); // Создаем контекст для хеширования
        if (!ctx) {
            throw std::runtime_error("Ошибка: не удалось создать контекст для хеширования.");
        }

        // Инициализация хеширования
        if (1 != EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr)) {
            EVP_MD_CTX_free(ctx);
            throw std::runtime_error("Ошибка: не удалось инициализировать хеширование.");
        }

        // Обновление данных для хеширования
        if (1 != EVP_DigestUpdate(ctx, input.c_str(), input.size())) {
            EVP_MD_CTX_free(ctx);
            throw std::runtime_error("Ошибка: не удалось обновить данные для хеширования.");
        }

        // Получение результата хеширования
        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int hashLength = 0;
        if (1 != EVP_DigestFinal_ex(ctx, hash, &hashLength)) {
            EVP_MD_CTX_free(ctx);
            throw std::runtime_error("Ошибка: не удалось получить результат хеширования.");
        }

        EVP_MD_CTX_free(ctx); // Освобождаем контекст

        // Преобразование хеша в строку
        std::ostringstream ss;
        for (unsigned int i = 0; i < hashLength; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        return ss.str();
    }

    // Сериализация данных
    json Serializable::serialize() const {
        json j;

        // Сериализация кораблей
        json ships = json::array();
        for (const auto& ship : shipman->GetShipArray()) {
            json shipJson;
            shipJson["index"] = ship.GetShipIndex();
            shipJson["length"] = ship.GetShipLength();
            shipJson["location"] = ship.GetLocation() == Ship::LocationShip::horizontal ? "horizontal" : "vertical";
            json segments = json::array();
            for (const auto& segment : ship.GetSegmentsState()) {
                segments.push_back(segment == Ship::ShipSegmentState::Full ? "Full" :
                                   segment == Ship::ShipSegmentState::Damaged ? "Damaged" : "Destroyed");
            }
            shipJson["segments"] = segments;
            ships.push_back(shipJson);
        }
        j["ships"] = ships;

        // Сериализация карты
        json mapJson;
        mapJson["height"] = map->SizeHeight();
        mapJson["width"] = map->SizeWidht();
        json cells = json::array();
        for (int y = 0; y < map->SizeHeight(); ++y) {
            for (int x = 0; x < map->SizeWidht(); ++x) {
                json cellJson;
                cellJson["x"] = x;
                cellJson["y"] = y;
                cellJson["state"] = map->GetCellState(x, y) == Map::MapCells::unknown ? "unknown" :
                                    map->GetCellState(x, y) == Map::MapCells::empty ? "empty" : "ship";
                cellJson["shipIndex"] = map->GetCell(x, y).GetShipAdress() ? map->GetCell(x, y).GetShipAdress()->GetShipIndex() : -1;
                cellJson["segmentIndex"] = map->GetCell(x, y).GetSegmentIndex();
                cells.push_back(cellJson);
            }
        }
        mapJson["cells"] = cells;
        j["map"] = mapJson;

        // Сериализация способностей
        json abilities = json::array();
        std::queue<IFactory*> abilities_creators = abilityManager->getAbilitiesCreators();
        while (!abilities_creators.empty()) {
            IFactory* ability_creator = abilities_creators.front();
            abilities_creators.pop();
            json abilityJson;
            if (dynamic_cast<DoubleDamageFactory*>(ability_creator)) {
                abilityJson["type"] = "DoubleDamage";
            } else if (dynamic_cast<ScannerFactory*>(ability_creator)) {
                abilityJson["type"] = "Scanner";
            } else if (dynamic_cast<BombardmentFactory*>(ability_creator)) {
                abilityJson["type"] = "Bombardment";
            }
            abilities.push_back(abilityJson);
        }
        j["abilities"] = abilities;

        // Вычисление хеша
        std::string serializedData = j.dump();
        j["hash"] = calculateHash(serializedData);

        return j;
    }

    // Десериализация данных
    void Serializable::deserialize(const json& j) {
        // Проверка хеша
        json dataWithoutHash = j; // Копируем JSON без хеша
        dataWithoutHash.erase("hash"); // Удаляем хеш из данных
        std::string serializedData = dataWithoutHash.dump(); // Сериализуем данные без хеша
        std::string savedHash = j["hash"]; // Сохраненный хеш
        std::string calculatedHash = calculateHash(serializedData); // Вычисляем хеш от данных без хеша

        if (savedHash != calculatedHash) {
            throw std::runtime_error("Ошибка: хеш сохраненных данных не совпадает с вычисленным. Файл может быть поврежден или изменен.");
        }

        // Десериализация кораблей
        shipman->ClearShips();
        for (const auto& shipJson : j["ships"]) {
            int index = shipJson["index"];
            int length = shipJson["length"];
            Ship::LocationShip location = shipJson["location"] == "horizontal" ? Ship::LocationShip::horizontal : Ship::LocationShip::vertical;
            Ship& ship = shipman->AddShip(length);
            ship.SetShipIndex(index);
            ship.SetLocation(location);
            std::vector<Ship::ShipSegmentState> segments;
            for (const auto& segment : shipJson["segments"]) {
                segments.push_back(segment == "Full" ? Ship::ShipSegmentState::Full :
                                   segment == "Damaged" ? Ship::ShipSegmentState::Damaged : Ship::ShipSegmentState::Destroyed);
            }
            ship.SetSegmentsState(segments);
        }

        // Десериализация карты
        int height = j["map"]["height"];
        int width = j["map"]["width"];
        map->SetSize(height, width);
        for (const auto& cellJson : j["map"]["cells"]) {
            int x = cellJson["x"];
            int y = cellJson["y"];
            Map::MapCells state = cellJson["state"] == "unknown" ? Map::MapCells::unknown :
                                  cellJson["state"] == "empty" ? Map::MapCells::empty : Map::MapCells::ship;
            map->SetCellState(x, y, state);
            int shipIndex = cellJson["shipIndex"];
            int segmentIndex = cellJson["segmentIndex"];
            if (shipIndex != -1) {
                Ship* ship = &shipman->GetShip(shipIndex);
                map->GetCell(x, y).SetShipAdress(ship);
                map->GetCell(x, y).SetSegmentIndex(segmentIndex);
            }
        }

        // Десериализация способностей
        abilityManager->clearAbilities();
        for (const auto& abilityJson : j["abilities"]) {
            std::string type = abilityJson["type"];
            if (type == "DoubleDamage") {
                abilityManager->addAbility(new DoubleDamageFactory());
            } else if (type == "Scanner") {
                abilityManager->addAbility(new ScannerFactory(*map, *coordHolder));
            } else if (type == "Bombardment") {
                abilityManager->addAbility(new BombardmentFactory(*map));
            }
        }
    }

