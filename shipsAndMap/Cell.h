#ifndef CELL_H
#define CELL_H

#include "ship.h"
#include "shipmanager.h"

class Cell {
public:
    enum class MapCells {
        unknown,
        empty,
        ship
    };

private:
    MapCells state;
    Ship* ship_adress;
    int segment_index;

public:
    Cell();

    void SetState(MapCells state);
    void SetShipAdress(Ship* ship_adress);
    void SetSegmentIndex(int segment_index);

    Ship* GetShipAdress();
    int GetSegmentIndex();
    MapCells GetState() const;
};

#endif 
