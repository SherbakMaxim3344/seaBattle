#ifndef OOP_LAB2_CONSOLERENDERER_H
#define OOP_LAB2_CONSOLERENDERER_H
#include <iostream>
#include "../shipsAndMap/map.h"


class ConsoleRenderer {
public:
    void printField(Map& field);

    void printMessage(const std::string& message);
};


#endif //OOP_LAB2_CONSOLERENDERER_H
