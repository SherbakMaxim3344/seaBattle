#ifndef OOP_LAB2_TERMINALHANDLER_H
#define OOP_LAB2_TERMINALHANDLER_H


#include <unordered_map>  
#include <string>      
#include <utility>       
#include <fstream>       
#include <iostream>       
#include <nlohmann/json.hpp>  
#include <unordered_map>
#include <unordered_set>
#include "nlohmann/json.hpp"
#include <openssl/evp.h>
#include "Command.h"  

using json = nlohmann::json;


class TerminalHandler {
private:
    std::unordered_map<char, Command> command_map; 
    std::unordered_map<std::string, char> command_key_map; 

    // Установка стандартных команд
    void setDefaultCommands();

    // Загрузка команд из файла
    bool loadCommandsFromFile(const std::string& filename);

    // Валидация команд из JSON
    bool validateCommands(const json& j);

public:
    // Конструктор
    TerminalHandler(const std::string& filename);

    // Получение команды по символу
    Command getCommand(char input);

    // Получение ввода от пользователя
    char getInput();

    // Вывод главного меню
    void printMainMenu();

    // Вывод меню игры
    void printGameMenu() ;

    // Вывод меню помощи
    void printHelpMenu();

    // Получение координат атаки от пользователя
    std::pair<int, int> getAttackCoordinates();
};




#endif //OOP_LAB2_TERMINALHANDLER_H
