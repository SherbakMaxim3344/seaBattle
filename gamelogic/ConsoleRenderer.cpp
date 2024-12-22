#include "ConsoleRenderer.h"


    void ConsoleRenderer::printField(Map& field) { // Переименовали drawField в printField
        // Печатаем заголовок для оси X
        std::cout << " "; // Пробел для выравнивания
        for (int j = 0; j < field.SizeWidht(); ++j) { // Начинаем с 0 для нулевой индексации
            std::cout << " " << j << " "; // Печатаем номер колонки
        }
        std::cout << std::endl; // Переход на следующую строку

        // Печатаем карту с номерами строк по оси Y
        for (int i = 0; i < field.SizeHeight(); ++i) { // Начинаем с 0 для нулевой индексации
            std::cout << i << " "; // Печатаем номер строки

            for (int j = 0; j < field.SizeWidht(); ++j) { // Начинаем с 0 для нулевой индексации
                Cell& cell = field.GetCell(j, i);
                if (cell.GetState() == Cell::MapCells::unknown) {
                    std::cout << "🟦 "; // Неизвестная клетка
                } else if (cell.GetState() == Cell::MapCells::ship) {
                    Ship* ship = cell.GetShipAdress(); // Получаем адрес корабля
                    if (ship != nullptr) { // Проверяем, что указатель не нулевой
                        switch (ship->GetSegmentState(cell.GetSegmentIndex())) {
                            case Ship::ShipSegmentState::Damaged:
                                std::cout << "⭕️ "; // Поврежденный сегмент
                                break;
                            case Ship::ShipSegmentState::Destroyed:
                                std::cout << "❌ "; // Уничтоженный сегмент
                                break;
                            case Ship::ShipSegmentState::Full:
                                std::cout << "🚢 "; // Целый сегмент
                                break;
                            default:
                                std::cout << "❓ "; // Если состояние неизвестно
                                break;
                        }
                    } else {
                        std::cout << "❎ "; // Если указатель на корабль нулевой
                    }
                } else if (cell.GetState() == Cell::MapCells::empty) {
                    std::cout << "⬜️ "; // Пустая клетка
                }
            }
            std::cout << std::endl; // Переход на следующую строку
        }
    }

    void ConsoleRenderer::printMessage(const std::string& message) {
        std::cout << message << std::endl;
    }
