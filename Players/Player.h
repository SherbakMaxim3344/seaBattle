#ifndef PLAYER_H
#define PLAYER_H

#include "../shipsAndMap/map.h"
#include "../shipsAndMap/shipmanager.h"
#include "../gamelogic/GameState.h"
#include "../Ability/Abilities.h"
#include "../Ability/AbilityResponce.h"
#include "../Ability/AbilityManager.h"
#include "../holders/inputHandler.h"
#include <set>
#include <random>
#include <iostream>

class Player {
protected:
    Map* map;
    ShipManager* shipManager;
    GameState* gameState;

public:
    Player(Map* map, ShipManager* shipManager, GameState* gameState) ;

    virtual void placeShips() = 0; // Чисто виртуальный метод для размещения кораблей
    virtual void attack(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager) = 0; // Метод для атаки
    virtual void useAbility(AbilityManager* skillManager, AbilityResponce* responce) = 0; // Метод для использования способности

    bool allShipsDestroyed();

    bool saveGameToFile() ;

    bool loadGameFromFile();
};

class HumanPlayer : public Player {
public:
    HumanPlayer(Map* map, ShipManager* shipManager, GameState* gameState);

    void placeShips() override ;

    void attack(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager) override;

    void useAbility(AbilityManager* skillManager, AbilityResponce* responce) override;
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer(Map* map, ShipManager* shipManager, GameState* gameState) ;

    void placeShips() override;

    void attack(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager) override;


    void useAbility(AbilityManager* skillManager, AbilityResponce* responce) override ;
};



#endif // PLAYER_H