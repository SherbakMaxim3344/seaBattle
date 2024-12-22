#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <iostream>
#include <limits>
#include <string>

class InputHandler {
public:
    static int getIntInput(const std::string& prompt);
};

class CoordReader {
public:
    std::pair<int, int> ReadCoords();
};

#endif // INPUT_HANDLER_H
