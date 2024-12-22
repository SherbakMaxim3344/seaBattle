#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include "ship.h"


class ShipManager {
private:
    std::vector<Ship> ship_array;

public:    
    ShipManager(int number_ships, std::vector<int>& size_ships);
    
    Ship& GetShip(int index);

    int GetShipCount();

    std::vector<Ship>& GetShipArray();

    void AddShip(const Ship& ship) ;
    // Метод для добавления корабля с указанным индексом
    Ship& AddShip(int length);
    // Метод для очистки всех кораблей
    void ClearShips();
    void RestoreShips();
};

#endif
