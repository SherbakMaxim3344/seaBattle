#include "Game.h"



    Game::Game() {
        initializeGame();
        std::cout << "Добро пожаловать в игру!\n";
    }

    Game::~Game() {
        cleanUp();
    }

    void Game::cleanUp() {
        delete myship;
        delete opponentsship;
        delete my_map;
        delete opponents_map;
        delete skillManager;
        delete responce;
        delete humanPlayer;
        delete computerPlayer;
        delete coordHolder;
        delete gameState;
    }

    void Game::initializeGame() {
        isRunningGame = false;
        isLoaded = false; // Изначально игра не загружена
        roundNumber = 1;
        std::vector<int> leng{1, 1};
        myship = new ShipManager(2, leng);
        opponentsship = new ShipManager(2, leng);
        responce = new AbilityResponce();
        coordHolder = new CoordHolder();

        my_map = new Map(10, 10, myship);
        opponents_map = new Map(10, 10, opponentsship);
        skillManager = new AbilityManager(*opponents_map, *coordHolder);

        gameState = new GameState(my_map, opponents_map, myship, opponentsship, skillManager, coordHolder);

        humanPlayer = new HumanPlayer(my_map, myship, gameState);
        computerPlayer = new ComputerPlayer(opponents_map, opponentsship, gameState);
    }

    void Game::gameStart() {
        std::cout << YELLOW << "Игра началась!" << RESET << '\n';
        isRunningGame = true;

        // Размещаем корабли игрока
        humanPlayer->placeShips();

        if (!isLoaded) { // Если игра не была загружена, размещаем корабли противника
            computerPlayer->placeShips();
        }
    }

    void Game::gameOver() {
        isRunningGame = false;
        std::cout << YELLOW << "Игра окончена!" << RESET << '\n';
    }
    void Game::nextRound() {
    roundNumber++; // Увеличиваем номер раунда

    // Восстанавливаем корабли противника
    opponentsship->RestoreShips();
    opponents_map->Clear();

    // Размещаем корабли противника для нового раунда
    computerPlayer->placeShips();

    std::cout << "Начался новый раунд! Текущий раунд: " << roundNumber << '\n';
}
void Game::restartGame() {
    roundNumber = 1; // Сбрасываем номер раунда

            cleanUp(); // Освобождаем память предыдущей игры
            initializeGame(); // Инициализируем новую игру

            gameStart();

    std::cout << "Игра перезапущена! Начинаем заново.\n";
}
    bool Game::loadGameFromFile() {
        return gameState->loadFromFile();
    }

    Map* Game::getMyMap() {
        return my_map;
    }

    Map* Game::getOpponentsMap() {
        return opponents_map;
    }

    bool Game::isGameOver() {
        return humanPlayer->allShipsDestroyed();
    }
    bool Game::newround(){
        return computerPlayer->allShipsDestroyed();
    }
    void Game::humanPlayerAttack() {
        humanPlayer->attack(opponents_map, responce, skillManager);
    }

    void Game::computerPlayerAttack() {
        computerPlayer->attack(my_map, responce, skillManager);
    }

    void Game::useAbility() {
        skillManager->activateAbility(*responce);
        responce->GetAbilityResult();
    }

    bool Game::saveGameToFile() {
        return gameState->saveToFile();
    }

    void Game::printField(Map& field) {
        field.print(true);
    }
