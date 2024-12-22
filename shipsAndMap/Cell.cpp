#include "Cell.h"

Cell::Cell() {
    this->state = MapCells::unknown;
    this->ship_adress = nullptr;
    this->segment_index = -1;
}

void Cell::SetState(MapCells state) {
    this->state = state;
}

void Cell::SetShipAdress(Ship* ship_adress) {
    this->ship_adress = ship_adress;
}

void Cell::SetSegmentIndex(int segment_index) {
    this->segment_index = segment_index;
}

Ship* Cell::GetShipAdress() {
    return ship_adress;
}

int Cell::GetSegmentIndex() {
    return segment_index;
}

Cell::MapCells Cell::GetState() const {
    return state;
}
