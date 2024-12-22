#ifndef OOP_LAB2_GAMECONTROLLER_H
#define OOP_LAB2_GAMECONTROLLER_H

#include "Game.h"
#include "TerminalHandler.h"
#include "Command.h"
#include <iostream>
#include <vector>
#include <optional>
#include <queue>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <set>
#include <exception>
#include <string>
#include <utility>
#include <filesystem>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include "nlohmann/json.hpp"
#include <openssl/evp.h>


template <typename InputHandler, typename Display>
class GameController {
private:
    Game& game;
    InputHandler& handler;
    Display& display;

public:
    GameController(Game& g, InputHandler& handler, Display& display) 
        : game(g), handler(handler), display(display) {}

    void start() {
        handler.printMainMenu();
        char command = handler.getInput();
        if (handler.getCommand(command) == Command::NewGame) {
            game.gameStart();
            return startLoop();
        } else if (handler.getCommand(command) == Command::LoadGame) {
            if (game.loadGameFromFile()) {
                display.printMessage("Игра загружена.");
                return startLoop();
            } else {
                display.printMessage("Не удалось загрузить игру. Начните новую игру.");
                return start();
            }
        } else if (handler.getCommand(command) == Command::Exit) {
            exit(0);
        } else if (handler.getCommand(command) == Command::None) { // Если игрок выбрал "Help"
            handler.printHelpMenu();
            return start();
        } else {
            display.printMessage("Ошибка: Неверная команда. Посмотрите назначения клавиш в меню помощи и нажмите соответствующую клавишу.");
            return start();
        }
    }

void startLoop() {
    while (true) {
        display.printMessage("Ваш ход:");
        display.printField(*game.getMyMap());
        display.printMessage("Карта противника:");
        display.printField(*game.getOpponentsMap());
        playerMove();

        // Проверяем, уничтожены ли все корабли противника
        if (game.newround()) {
            game.nextRound(); // Переходим к новому раунду
            continue; // Пропускаем ход противника, так как раунд только начался
        }

        if (game.isGameOver()) {
            display.printMessage("Игра окончена.");
            game.restartGame(); // Перезапускаем игру, если все корабли игрока уничтожены
            continue; // Начинаем игру заново
        }

        computerMove();

        // Проверяем, уничтожены ли все корабли игрока
        if (game.isGameOver()) {
            display.printMessage("Игра окончена.");
            game.restartGame(); // Перезапускаем игру, если все корабли игрока уничтожены
            continue; // Начинаем игру заново
        }
    }
}

    void playerMove() {
        bool playerAttacked = false; // Флаг, указывающий, атаковал ли игрок

        while (!playerAttacked) { // Цикл для повторного запроса команды, пока игрок не атакует
            handler.printGameMenu();
            char commandChar = handler.getInput();
            Command command = handler.getCommand(commandChar);

            if (command == Command::Attack) {
                game.humanPlayerAttack();
                playerAttacked = true; // Игрок атаковал, выходим из цикла
            } else if (command == Command::UseAbility) {
                game.useAbility();
                display.printMessage("Способность использована.");
            } else if (command == Command::SaveGame) {
                if (game.saveGameToFile()) {
                    display.printMessage("Игра сохранена.");
                } else {
                    display.printMessage("Не удалось сохранить игру.");
                }
            } else if (command == Command::LoadGame) {
                if (game.loadGameFromFile()) {
                    display.printMessage("Игра загружена.");
                } else {
                    display.printMessage("Не удалось загрузить игру.");
                }
            } else if (command == Command::None) { // Если команда "Help"
                handler.printHelpMenu();
            } else if (command == Command::Exit) {
                exit(0);
            } else {
                display.printMessage("Ошибка: Неверная команда. Посмотрите назначения клавиш в меню помощи и нажмите соответствующую клавишу.");
            }
        }
    }

    void computerMove() {
        display.printMessage("Ход противника:");
        game.computerPlayerAttack();
    }
};


#endif // OOP_LAB2_GAMECONTROLLER_H