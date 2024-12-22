#ifndef OOP_LAB2_GAME_H
#define OOP_LAB2_GAME_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "GameState.h"
#include "../Players/Player.h"
#include "../shipsAndMap/map.h"
#include "../shipsAndMap/shipmanager.h"
#include "../Ability/AbilityManager.h"
#include "../holders/holders.h"
#include "../Ability/AbilityResponce.h"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"

class Game {
private:
    bool isRunningGame;
    bool isLoaded; // Флаг, указывающий, была ли игра загружена
    Map* my_map;
    Map* opponents_map;
    AbilityManager* skillManager;
    AbilityResponce* responce;
    Player* humanPlayer;
    Player* computerPlayer;
    CoordHolder* coordHolder;
    GameState* gameState;
    int roundNumber; // Добавляем номер раунда
    ShipManager* myship;
    ShipManager* opponentsship;

public:
    Game();

    ~Game();

    void cleanUp();

    void initializeGame();

    void gameStart();

    void gameOver();
    void nextRound();
    void restartGame();
    bool loadGameFromFile() ;

    Map* getMyMap();

    Map* getOpponentsMap();

    bool isGameOver() ;
    bool newround();
    void humanPlayerAttack() ;

    void computerPlayerAttack();

    void useAbility();

    bool saveGameToFile();

    void printField(Map& field);
};

#endif //GAME