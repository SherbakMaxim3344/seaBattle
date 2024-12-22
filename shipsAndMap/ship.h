#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>
#include <vector>

class Ship{
public:
    enum class ShipSegmentState {
        Full,
        Damaged,
        Destroyed
    };
    enum class LocationShip{
        horizontal,
        vertical
    };
private:
    std::vector<ShipSegmentState> segments;
    int lenght_ship; 
    int index;
    LocationShip location_ship; 
public:
    Ship(int lenght);

    void DamageSegment(int segment_index, int hpdamage);
    bool isDestroyed() const;
    int GetShipLength() const;
    void SetShipLength(int lenght_ship);
    int GetShipIndex() const;
    void SetShipIndex(int index);
    LocationShip GetLocation() const;
    void SetLocation(LocationShip location_ship);
    std::vector<ShipSegmentState> GetSegmentsState() const;
    void SetSegmentsState(const std::vector<ShipSegmentState>& newSegments);
    ShipSegmentState GetSegmentState(int segment_index) const;
    void Restore();
};

#endif