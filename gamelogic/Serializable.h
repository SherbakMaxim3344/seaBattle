#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "../shipsAndMap/map.h"
#include "../shipsAndMap/Cell.h"
#include "../shipsAndMap/shipmanager.h"
#include "../Ability/AbilityManager.h"
#include "../holders/holders.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <unordered_map>
#include <functional>
#include <filesystem>
#include <openssl/sha.h>
using json = nlohmann::json;






class Serializable {
private:
    Map* map;
    ShipManager* shipman;
    AbilityManager* abilityManager;
    CoordHolder* coordHolder;

public:
    Serializable(Map* map, ShipManager* shipman, AbilityManager* abilityManager, CoordHolder* coordHolder);

    // Метод для вычисления SHA-256 хеша
    std::string calculateHash(const std::string& input) const;

    // Сериализация данных
    json serialize() const;

    // Десериализация данных
    void deserialize(const json& j);
};

#endif