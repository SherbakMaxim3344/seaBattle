#include "Abilities.h"
#include "../shipsAndMap/map.h"
    
    DoubleDamage::DoubleDamage(){};

    void DoubleDamage::use(AbilityResponce& responce) {
        responce.SetLastAbility(AbilityResponce::Ability::DoubleDamage);
        responce.DoubleDamageActivated();
    }



    Scanner::Scanner(Map& map, int x, int y) : map(map){
        this->x=x;
        this->y=y;
    }
    void Scanner::use(AbilityResponce& responce) {
        responce.SetLastAbility(AbilityResponce::Ability::Scanner);
        int map_h = map.SizeHeight();
        int map_w = map.SizeWidht();
        

        if (x < 0 || x >= map_w || y < 0 || y >= map_h) {
            throw OutOfBoundsException("Ошибка: координаты выхода за границы поля");
        }

        bool shipFound = false; 
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                int check_x = x + j;
                int check_y = y + i;
                if (check_x >= map_w || check_y >= map_h) {
                    continue; 
                }

                Ship* ship = map.GetCell(check_x, check_y).GetShipAdress(); 
                if (ship && ship->GetSegmentState(map.GetCell(check_x, check_y).GetSegmentIndex()) != Ship::ShipSegmentState::Destroyed) {
                    responce.ScanSuccessful();
                    shipFound = true; 
                    break; 
                }
            }
            if (shipFound) break; 
        }
        
        if (!shipFound) {
            responce.ScanEmpty();
        }
    }





    Bombardment::Bombardment(Map& map) : map(map) {}

    void Bombardment::use(AbilityResponce& responce) {
        responce.SetLastAbility(AbilityResponce::Ability::Bombardment);
        ShipManager& manager = map.GetShipManager();
        std::vector<std::pair<int, int>> ship_segments;

        for (int y = 0; y < manager.GetShipCount(); y++) {
            for (int x = 0; x < manager.GetShip(y).GetShipLength(); x++) {
                if (manager.GetShip(y).GetSegmentState(x) != Ship::ShipSegmentState::Destroyed) {
                    ship_segments.emplace_back(y, x);
                }
            }
        }

        if (!ship_segments.empty()) {
            int random_index = rand() % ship_segments.size();
            int y = ship_segments[random_index].first;
            int x = ship_segments[random_index].second;

            try {
                manager.GetShip(y).DamageSegment(x, 1);
            } catch (const EventHandler& e) {
                throw EventHandler{"Ошибка: не удалось повредить сегмент, он уже уничтожен."};  
            }
        } else {
            throw EventHandler{"Ошибка: нет доступных сегментов для повреждения."};  
        }
    }
