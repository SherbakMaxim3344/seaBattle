#include "shipmanager.h"

  
 
    ShipManager::ShipManager(int number_ships, std::vector<int>& size_ships) {
        for (int i = 0; i < number_ships; i++) {
            int k=size_ships.size();
                ship_array.emplace_back(Ship(size_ships[i])); 
                ship_array[i].SetShipIndex(i);
        }
    }
    
    Ship& ShipManager::GetShip(int index) {
        return ship_array[index]; 
    }

    int ShipManager::GetShipCount(){
        return ship_array.size();
    }

    std::vector<Ship>& ShipManager::GetShipArray() {
        return ship_array;
    }

    void ShipManager::AddShip(const Ship& ship) {
        ship_array.push_back(ship);
    }

    // Метод для добавления корабля с указанным индексом
    Ship& ShipManager::AddShip(int length) {
        int index = ship_array.size();
        ship_array.emplace_back(Ship(length));
        ship_array.back().SetShipIndex(index);
        return ship_array.back();
    }

    // Метод для очистки всех кораблей
    void ShipManager::ClearShips() {
        ship_array.clear();
    }
    void ShipManager::RestoreShips() {
        for (auto& ship : ship_array) {
            ship.Restore();
        }
    }

