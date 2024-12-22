#include "inputHandler.h"

int InputHandler::getIntInput(const std::string& prompt) {
    int input;
    std::cout << prompt;
    while (true) {
        if (std::cin >> input) {
            return input;
        } else {
            std::cout << "Некорректный ввод. Попробуйте снова: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << prompt;
    }
}

std::pair<int, int> CoordReader::ReadCoords() {
    int x = InputHandler::getIntInput("Введите координату x: ");
    int y = InputHandler::getIntInput("Введите координату y: ");
    return {x, y};
}
