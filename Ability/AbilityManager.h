#ifndef ABILITYMANAGER_H 
#define ABILITYMANAGER_H


#include <queue>
#include <memory>
#include <algorithm>
#include <random>
#include "Abilities.h"
#include "../factory/factories.h"
#include "../exceptions/exceptions.h"
class Map;

class AbilityManager {
private:
    CoordHolder& coordinates_holder;
    Map& map;
    std::queue<IFactory*> abilities_creators;
    int total_abilities; 

public:
    AbilityManager(Map& map, CoordHolder& coordinates_holder);

    void AddRandomSkill();

    void activateAbility(AbilityResponce& response);

    int getTotalAbilities() const;
        std::queue<IFactory*> getAbilitiesCreators() const;
    void clearAbilities();
    void addAbility(IFactory* ability);
};

#endif