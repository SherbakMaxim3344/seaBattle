#include "AbilityManager.h"


    AbilityManager::AbilityManager(Map& map, CoordHolder& coordinates_holder) 
        : map(map), coordinates_holder(coordinates_holder), total_abilities(0) {

        std::random_device rd;
        std::default_random_engine rng(rd());

        std::vector<IFactory*> temporary_abilities;
        temporary_abilities.push_back(new DoubleDamageFactory());
        temporary_abilities.push_back(new ScannerFactory(map, coordinates_holder));
        temporary_abilities.push_back(new BombardmentFactory(map));
    
        std::shuffle(temporary_abilities.begin(), temporary_abilities.end(), rng);
        
        for (auto& ability : temporary_abilities) {
            abilities_creators.push(ability);
            total_abilities++; 
        }
    }

    void AbilityManager::AddRandomSkill() {
        int random_ability = rand() % 3;
        switch (random_ability) {
            case 0:
                abilities_creators.push(new DoubleDamageFactory());
                break;
            case 1:
                abilities_creators.push(new ScannerFactory(map, coordinates_holder));
                break;
            case 2:
                abilities_creators.push(new BombardmentFactory(map));
                break;
        }
        total_abilities++; 
    }

    void AbilityManager::activateAbility(AbilityResponce& response) {
        if (abilities_creators.empty()) {
            throw NoAbilitiesException("ошибка: способностей нет");
        }

        IFactory* ability_creator = abilities_creators.front();
        abilities_creators.pop();

        IAbility* ability = ability_creator->createAbility();
        delete ability_creator;
        ability->use(response);
        delete ability;
    }

    int AbilityManager::getTotalAbilities() const { 
        return total_abilities;
    }

        std::queue<IFactory*> AbilityManager::getAbilitiesCreators() const {
        return abilities_creators;
    }

    void AbilityManager::clearAbilities() {
        while (!abilities_creators.empty()) {
            delete abilities_creators.front();
            abilities_creators.pop();
        }
    }

    void AbilityManager::addAbility(IFactory* ability) {
        abilities_creators.push(ability);
    }