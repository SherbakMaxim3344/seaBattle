#include "ship.h"
#include "../exceptions/exceptions.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>


    Ship::Ship(int lenght){
        if(lenght<1 || lenght>4){
            std::cout<< lenght << "недопустимый размер корабля изменен на 2\n";
            lenght=2;
        }
        lenght_ship=lenght;
        segments.resize(lenght,ShipSegmentState::Full);
    } 
 
    
    void Ship::DamageSegment(int segment_index, int hpdamage){
        if (segment_index >= 0 && segment_index < lenght_ship){              
                if (segments[segment_index] == ShipSegmentState::Full){  
                    if(hpdamage==1){                       
                        segments[segment_index] = ShipSegmentState::Damaged;
                    }else if(hpdamage==2){
                        segments[segment_index] = ShipSegmentState::Destroyed;
                    }
                }else if (segments[segment_index] == ShipSegmentState::Damaged){
                    segments[segment_index] = ShipSegmentState::Destroyed;
                }else{
                    throw EventHandler{"ошибка: сегмент уже уничтожен"};            
                }
        }
    }

    bool Ship::isDestroyed() const {
        for (const auto& segment : segments) {
            if (segment != ShipSegmentState::Destroyed) {
                return false; 
            }
        }
        return true; 
    }

    int Ship::GetShipLength() const {
        return lenght_ship;
    }
    void Ship::SetShipLength(int lenght_ship){
        this->lenght_ship = lenght_ship;
    }
    
    int Ship::GetShipIndex() const{
        return index;
    }
    void Ship::SetShipIndex(int index){
        this->index = index;
    }

    Ship::LocationShip Ship::GetLocation() const {
        return location_ship;
    }
    void Ship::SetLocation(LocationShip location_ship){
        this->location_ship= location_ship;
    }
    
    std::vector<Ship::ShipSegmentState> Ship::GetSegmentsState() const {
        return segments;
    }
    void Ship::SetSegmentsState(const std::vector<ShipSegmentState>& newSegments) {
        segments = newSegments;
    }




    Ship::ShipSegmentState Ship::GetSegmentState(int segment_index) const{
        return segments[segment_index];
    }
    void Ship::Restore() {
        segments.assign(lenght_ship, ShipSegmentState::Full);
    }