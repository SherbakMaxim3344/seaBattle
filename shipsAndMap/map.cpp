#include "map.h"





Map::Map(int size_map_height, int size_map_width, ShipManager* manager)
{
    this->size_map_width = size_map_width;
    this->size_map_height = size_map_height; 
    starting_map.resize(size_map_height, std::vector<Cell>(size_map_width));
    this->manager = manager;
}




void Map::ShipPlacement(int index, int coordinate_x, int coordinate_y, Ship::LocationShip location_ship) {
    Ship& ship = manager->GetShip(index);

    // Проверка на допустимость расположения корабля
    if (location_ship != Ship::LocationShip::vertical && location_ship != Ship::LocationShip::horizontal) {
        std::cout << "недопустимое расположение корабля, изменено на horizontal" << '\n';
        location_ship = Ship::LocationShip::horizontal; // Изменяем на горизонтальное
    }

    ship.SetLocation(location_ship);

    if (location_ship == Ship::LocationShip::horizontal) {
        // Проверка на выход за границы карты по ширине
        if (coordinate_x < 0 || coordinate_x + ship.GetShipLength() > size_map_width) {
            throw ShipPlacementException("ошибка: Корабль выходит за границы карты по ширине");
        }

        // Проверка на пересечение с другими кораблями и их окружением
        for (int i = 0; i < ship.GetShipLength(); i++) {
            // Проверка верхней строки
            if (coordinate_y > 0) {
                if (coordinate_x + i > 0 && starting_map[coordinate_y - 1][coordinate_x + i - 1].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
                if (starting_map[coordinate_y - 1][coordinate_x + i].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
                if (coordinate_x + i < size_map_width - 1 && starting_map[coordinate_y - 1][coordinate_x + i + 1].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
            }

            // Проверка текущей строки
            if (coordinate_x > 0 && starting_map[coordinate_y][coordinate_x + i - 1].GetState() == Cell::MapCells::ship) {
                throw ShipPlacementException("ошибка: корабль пересекается");
            }
            if (coordinate_x + i < size_map_width - 1 && starting_map[coordinate_y][coordinate_x + i + 1].GetState() == Cell::MapCells::ship) {
                throw ShipPlacementException("ошибка: корабль пересекается");
            }

            // Проверка нижней строки
            if (coordinate_y < size_map_height - 1) {
                if (coordinate_x + i > 0 && starting_map[coordinate_y + 1][coordinate_x + i - 1].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
                if (starting_map[coordinate_y + 1][coordinate_x + i].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
                if (coordinate_x + i < size_map_width - 1 && starting_map[coordinate_y + 1][coordinate_x + i + 1].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
            }
        }

        // Установка сегментов корабля на карту
        for (int i = 0; i < ship.GetShipLength(); i++) {
            starting_map[coordinate_y][coordinate_x + i].SetShipAdress(&ship);
            starting_map[coordinate_y][coordinate_x + i].SetSegmentIndex(i);
            starting_map[coordinate_y][coordinate_x + i].SetState(Cell::MapCells::ship);
        }
    } else if (location_ship == Ship::LocationShip::vertical) {
        // Проверка на выход за границы карты по высоте
        if (coordinate_y < 0 || coordinate_y + ship.GetShipLength() > size_map_height) {
            throw ShipPlacementException("ошибка: Корабль выходит за границы карты по высоте");
        }

        // Проверка на пересечение с другими кораблями и их окружением
        for (int i = 0; i < ship.GetShipLength(); i++) {
            // Проверка левого столбца
            if (coordinate_x > 0) {
                if (coordinate_y + i > 0 && starting_map[coordinate_y + i - 1][coordinate_x - 1].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
                if (starting_map[coordinate_y + i][coordinate_x - 1].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
                if (coordinate_y + i < size_map_height - 1 && starting_map[coordinate_y + i + 1][coordinate_x - 1].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
            }

            // Проверка текущего столбца
            if (coordinate_y > 0 && starting_map[coordinate_y + i - 1][coordinate_x].GetState() == Cell::MapCells::ship) {
                throw ShipPlacementException("ошибка: корабль пересекается");
            }
            if (coordinate_y + i < size_map_height - 1 && starting_map[coordinate_y + i + 1][coordinate_x].GetState() == Cell::MapCells::ship) {
                throw ShipPlacementException("ошибка: корабль пересекается");
            }

            // Проверка правого столбца
            if (coordinate_x < size_map_width - 1) {
                if (coordinate_y + i > 0 && starting_map[coordinate_y + i - 1][coordinate_x + 1].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
                if (starting_map[coordinate_y + i][coordinate_x + 1].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
                if (coordinate_y + i < size_map_height - 1 && starting_map[coordinate_y + i + 1][coordinate_x + 1].GetState() == Cell::MapCells::ship) {
                    throw ShipPlacementException("ошибка: корабль пересекается");
                }
            }
        }

        // Установка сегментов корабля на карту
        for (int i = 0; i < ship.GetShipLength(); i++) {
            starting_map[coordinate_y + i][coordinate_x].SetShipAdress(&ship);
            starting_map[coordinate_y + i][coordinate_x].SetSegmentIndex(i);
            starting_map[coordinate_y + i][coordinate_x].SetState(Cell::MapCells::ship);
        }
    }
}

   
    bool Map::ShootingBattlefield(int x, int y, std::optional<AbilityResponce*> abilities_status) {
        // Проверка на выход за границы поля
        if (x < 0 || x >= size_map_width || y < 0 || y >= size_map_height) {
            throw OutOfBoundsException("Ошибка: координаты выхода за границы поля");
        }

        Ship * ship = starting_map[y][x].GetShipAdress();
        if(ship != nullptr && ship->GetSegmentState(starting_map[y][x].GetSegmentIndex()) != Ship::ShipSegmentState::Destroyed){
            
            if (starting_map[y][x].GetState() == Cell::MapCells::unknown) 
            {
                starting_map[y][x].SetState(Cell::MapCells::ship); 
            }

            if (abilities_status.has_value()){
                if(abilities_status.value()->GetDoubleDamageStatus() == AbilityResponce::DoubleDamageStatus::activated && ship->GetSegmentState(starting_map[y][x].GetSegmentIndex()) == Ship::ShipSegmentState::Full){
                    ship->DamageSegment(starting_map[y][x].GetSegmentIndex(), 2);
                }else{
                    ship->DamageSegment(starting_map[y][x].GetSegmentIndex(), 1);
                }
                abilities_status.value()->DoubleDamageDisable();
            }else{
                ship->DamageSegment(starting_map[y][x].GetSegmentIndex(), 1);
            }

            if (ship->isDestroyed())
            {
                return true;
            }
            return false;
        }

        starting_map[y][x].SetState(Cell::MapCells::empty);
        return false;
    }


    void Map::print(bool myplace) {
        // Печатаем заголовок для оси X
        std::cout << " "; // Пробел для выравнивания
        for (int j = 0; j < size_map_width; ++j) { // Начинаем с 0 для нулевой индексации
            std::cout << " " << j << " "; // Печатаем номер колонки
        }
        std::cout << std::endl; // Переход на следующую строку

        // Печатаем карту с номерами строк по оси Y
        for (int i = 0; i < size_map_height; ++i) { // Начинаем с 0 для нулевой индексации
            std::cout << i << " "; // Печатаем номер строки

            for (int j = 0; j < size_map_width; ++j) { // Начинаем с 0 для нулевой индексации
                if (starting_map[i][j].GetState() == Cell::MapCells::unknown) {
                    std::cout << "🟦 "; // Неизвестная клетка
                } else if (starting_map[i][j].GetState() == Cell::MapCells::ship) {
                    Ship* ship = starting_map[i][j].GetShipAdress(); // Получаем адрес корабля
                    if (ship != nullptr) { // Проверяем, что указатель не нулевой
                        switch (ship->GetSegmentState(starting_map[i][j].GetSegmentIndex())) {
                            case Ship::ShipSegmentState::Damaged:
                                std::cout << "⭕️ "; // Поврежденный сегмент
                                break;
                            case Ship::ShipSegmentState::Destroyed:
                                std::cout << "❌ "; // Уничтоженный сегмент
                                break;
                            case Ship::ShipSegmentState::Full:
                                if(myplace==true){
                                    std::cout << "🚢 "; // Целый сегмент
                                }else{
                                    std::cout << "🚢 ";
                                }
                                break;
                            default:
                                std::cout << "❓ "; // Если состояние неизвестно
                                break;
                        }
                    } else {
                        std::cout << "❎ "; // Если указатель на корабль нулевой
                    }
                } else if (starting_map[i][j].GetState() == Cell::MapCells::empty) {
                    std::cout << "⬜️ "; // Пустая клетка
                }
            }
            std::cout << std::endl; // Переход на следующую строку
        }
    }


    // Конструктор копирования
    Map::Map(const Map& other) {
        size_map_height=other.size_map_height;
        size_map_width=other.size_map_width;
        starting_map=other.starting_map;
    }

    Map& Map::operator=(const Map& other) {
        if (this == &other) {
            return *this;
        }
        size_map_height=other.size_map_height;
        size_map_width=other.size_map_width;
        starting_map=other.starting_map;
        return *this;
    }

        // move constructor and assignment operator
   Map::Map(Map&& other) noexcept{
        size_map_height=other.size_map_height;
        size_map_width=other.size_map_width;
        starting_map=other.starting_map;
    }
    
    Map& Map::operator=(Map&& other) noexcept{
        if (this == &other) return *this;

        size_map_height=other.size_map_height;
        size_map_width=other.size_map_width;
        starting_map=std::move(other.starting_map);
        return *this;
    }

    int Map::SizeHeight(){
        return size_map_height;
    }
    int Map::SizeWidht(){
        return size_map_width;
    }
    
    Cell& Map::GetCell(int x, int y){
        return starting_map[y][x];
    }

    ShipManager& Map::GetShipManager(){
        return *manager;
    }

        // Метод для преобразования Cell::MapCells в Map::MapCells
     Map::MapCells Map::ConvertCellStateToMapState(Cell::MapCells cellState) {
        switch (cellState) {
            case Cell::MapCells::unknown: return MapCells::unknown;
            case Cell::MapCells::empty: return MapCells::empty;
            case Cell::MapCells::ship: return MapCells::ship;
            default: throw std::runtime_error("Неизвестное состояние ячейки");
        }
    }

    // Метод для преобразования Map::MapCells в Cell::MapCells
     Cell::MapCells Map::ConvertMapStateToCellState(MapCells mapState) {
        switch (mapState) {
            case MapCells::unknown: return Cell::MapCells::unknown;
            case MapCells::empty: return Cell::MapCells::empty;
            case MapCells::ship: return Cell::MapCells::ship;
            default: throw std::runtime_error("Неизвестное состояние карты");
        }
    }

    // Метод для установки размеров карты
    void Map::SetSize(int height, int width) {
        size_map_height = height;
        size_map_width = width;
        starting_map.resize(height, std::vector<Cell>(width));
    }

    // Метод для получения состояния ячейки
    Map::MapCells Map::GetCellState(int x, int y) const {
        return ConvertCellStateToMapState(starting_map[y][x].GetState());
    }

    // Метод для установки состояния ячейки
    void Map::SetCellState(int x, int y, MapCells state) {
        starting_map[y][x].SetState(ConvertMapStateToCellState(state));
    }

        // Метод для очистки карты
    void Map::Clear() {
        for (int y = 0; y < size_map_height; ++y) {
            for (int x = 0; x < size_map_width; ++x) {
                starting_map[y][x].SetState(Cell::MapCells::unknown);
                starting_map[y][x].SetShipAdress(nullptr);
                starting_map[y][x].SetSegmentIndex(-1);
            }
        }
    }