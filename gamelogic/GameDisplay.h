#ifndef OOP_LAB2_GAMEDISPLAY_H
#define OOP_LAB2_GAMEDISPLAY_H

#include "../shipsAndMap/map.h"
#include <iostream>

template <typename Renderer>
class GameDisplay {
private:
    Renderer renderer;

public:
    GameDisplay(Renderer& renderer) : renderer(renderer) {}

    void printField(Map& field) {
        renderer.printField(field); 
    }

    void printMessage(const std::string& message) {
        renderer.printMessage(message);
    }
};

#endif // OOP_LAB2_GAMEDISPLAY_H