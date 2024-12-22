#include "holders.h"


void CoordHolder::RequestData() {
    coords = coord_reader.ReadCoords();
}

std::pair<int, int> CoordHolder::GetCoords() {
    return coords;
}
