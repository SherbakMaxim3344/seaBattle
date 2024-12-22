#include "Player.h"



    Player::Player(Map* map, ShipManager* shipManager, GameState* gameState) 
        : map(map), shipManager(shipManager), gameState(gameState) {}

    bool Player::allShipsDestroyed() {
        for (int i = 0; i < shipManager->GetShipCount(); ++i) {
            Ship& ship = shipManager->GetShip(i);
            if (!ship.isDestroyed()) {
                return false; // Если хотя бы один корабль не уничтожен, возвращаем false
            }
        }
        return true; // Все корабли уничтожены
    }

    bool Player::saveGameToFile() {
        return gameState->saveToFile();
    }

    bool Player::loadGameFromFile() {
        return gameState->loadFromFile();
    }



    HumanPlayer::HumanPlayer(Map* map, ShipManager* shipManager, GameState* gameState) 
        : Player(map, shipManager, gameState) {}

    void HumanPlayer::placeShips()  {
        try {
            map->ShipPlacement(0, 1, 1, Ship::LocationShip::horizontal);
            map->ShipPlacement(1, 5, 9, Ship::LocationShip::horizontal);
            std::cout << "Ваши корабли размещены." << '\n';
        } catch (const ShipPlacementException& e) {
            std::cout << "Ошибка размещения корабля: " << e.what() << '\n';
        }
    }

    void HumanPlayer::attack(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager)  {
        int x = InputHandler::getIntInput("Введите координату x: ");
        int y = InputHandler::getIntInput("Введите координату y: ");
        auto res = opponentMap->ShootingBattlefield(x, y, responce);
        if (res == 1) {
            skillManager->AddRandomSkill();
        }
    }

    void HumanPlayer::useAbility(AbilityManager* skillManager, AbilityResponce* responce)  {
        if (responce != nullptr) {
            skillManager->activateAbility(*responce);
            responce->GetAbilityResult();
        } else {
            std::cout << "Ошибка: responce равен nullptr" << '\n';
        }
    }



    ComputerPlayer::ComputerPlayer(Map* map, ShipManager* shipManager, GameState* gameState) 
        : Player(map, shipManager, gameState) {}

    void ComputerPlayer::placeShips()  {
        srand(static_cast<unsigned>(time(0)));

        int shipsPlaced = 0; // Счетчик успешно размещенных кораблей

        while (shipsPlaced < 2) { 
            int x = rand() % map->SizeWidht();
            int y = rand() % map->SizeHeight();
            Ship::LocationShip direction = static_cast<Ship::LocationShip>(rand() % 2);

            try {
                map->ShipPlacement(shipsPlaced, x, y, direction);
                shipsPlaced++; // Увеличиваем счетчик только при успешном размещении
            } catch (const ShipPlacementException& e) {
                // Просто игнорируем ошибку и пробуем снова
            }
        }

        std::cout << "Корабли противника размещены." << '\n';
    }

    void ComputerPlayer::attack(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager)  {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> disWidth(0, opponentMap->SizeWidht() - 1);
        std::uniform_int_distribution<> disHeight(0, opponentMap->SizeHeight() - 1);

        std::set<std::pair<int, int>> attackedCells; // Множество для хранения атакованных клеток
        bool attacked = false;

        while (!attacked) {
            int x = disWidth(gen);
            int y = disHeight(gen);

            // Проверяем, была ли клетка уже атакована
            if (attackedCells.find({x, y}) == attackedCells.end()) {
                try {
                    opponentMap->ShootingBattlefield(x, y, std::nullopt);
                    attackedCells.insert({x, y}); // Добавляем клетку в множество атакованных
                    attacked = true; // Успешная атака
                } catch (const OutOfBoundsException& e) {
                    std::cout << e.what() << '\n';
                } catch (const AlreadyAttackedException& e) {
                    // Обработка исключения, если клетка уже была атакована
                }
            }
        }
    }

    void ComputerPlayer::useAbility(AbilityManager* skillManager, AbilityResponce* responce)  {
        // Компьютер не использует способности
        std::cout << "Компьютер не использует способности." << '\n';
    }


