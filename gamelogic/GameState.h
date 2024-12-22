#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "nlohmann/json.hpp"
#include "../Ability/AbilityManager.h"
#include "Serializable.h"

class GameState {
private:
    Map* my_map;
    Map* opponents_map;
    ShipManager* my_ship_manager;
    ShipManager* opponents_ship_manager;
    AbilityManager* abilityManager;
    CoordHolder* coordHolder;
    std::string saveFilePath = "savefile.json"; 

public:
    GameState(Map* my_map, Map* opponents_map, ShipManager* my_ship_manager, ShipManager* opponents_ship_manager, AbilityManager* abilityManager, CoordHolder* coordHolder);


    bool saveToFile() const;

    bool loadFromFile();
};

#endif // GAME_STATE_H