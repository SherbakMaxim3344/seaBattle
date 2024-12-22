#include "TerminalHandler.h"


    void TerminalHandler::setDefaultCommands() {
        command_key_map["New game"] = 'n';
        command_key_map["Attack"] = 'a';
        command_key_map["Use ability"] = 'e';
        command_key_map["Save game"] = 's';
        command_key_map["Load game"] = 'l';
        command_key_map["Exit"] = 'q';
        command_key_map["Help"] = 'h'; 


        command_map[command_key_map["New game"]] = Command::NewGame;
        command_map[command_key_map["Attack"]] = Command::Attack;
        command_map[command_key_map["Use ability"]] = Command::UseAbility;
        command_map[command_key_map["Save game"]] = Command::SaveGame;
        command_map[command_key_map["Load game"]] = Command::LoadGame;
        command_map[command_key_map["Exit"]] = Command::Exit;
        command_map[command_key_map["Help"]] = Command::None; 
    }


    bool TerminalHandler::loadCommandsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false; 
    }

    json j;
    file >> j; 
    if (!validateCommands(j)) {
        return false; 
    }


    command_map.clear();
    command_key_map.clear();


    for (auto& [key, value] : j.items()) {
        char command_char = value.get<std::string>()[0];
        if (key == "Attack") {
            command_key_map["Attack"] = command_char;
            command_map[command_char] = Command::Attack;
        } else if (key == "Use ability") {
            command_key_map["Use ability"] = command_char;
            command_map[command_char] = Command::UseAbility;
        } else if (key == "Save game") {
            command_key_map["Save game"] = command_char;
            command_map[command_char] = Command::SaveGame;
        } else if (key == "Load game") {
            command_key_map["Load game"] = command_char;
            command_map[command_char] = Command::LoadGame;
        } else if (key == "Exit") {
            command_key_map["Exit"] = command_char;
            command_map[command_char] = Command::Exit;
        } else if (key == "New game") {
            command_key_map["New game"] = command_char;
            command_map[command_char] = Command::NewGame;
        } else if (key == "Help") {
            command_key_map["Help"] = command_char;
            command_map[command_char] = Command::None; 
        }
    }

    return true;
}


    bool TerminalHandler::validateCommands(const json& j) {
    std::vector<std::string> required_commands = {"Attack", "Use ability", "Save game", "Load game", "Exit", "New game", "Help"};
    std::unordered_set<std::string> assigned_commands;
    std::unordered_set<char> used_keys;

    for (const auto& [command, key_json] : j.items()) {
        if (std::find(required_commands.begin(), required_commands.end(), command) == required_commands.end()) {
            return false; 
        }

        if (assigned_commands.find(command) != assigned_commands.end()) {
            return false; 
        }

        std::string key = key_json.get<std::string>();
        if (key.empty()) {
            return false; 
        }

        char key_char = key[0];

        if (used_keys.find(key_char) != used_keys.end()) {
            return false;
        }

        assigned_commands.insert(command);
        used_keys.insert(key_char);
    }

    for (const auto& command : required_commands) {
        if (assigned_commands.find(command) == assigned_commands.end()) {
            return false; 
        }
    }

    return true;
}


    TerminalHandler::TerminalHandler(const std::string& filename) {
    if (!loadCommandsFromFile(filename)) {
        setDefaultCommands(); 
    }

    std::vector<std::string> required_commands = {"Attack", "Use ability", "Save game", "Load game", "Exit", "New game", "Help"};
    for (const auto& command : required_commands) {
        if (command_key_map.find(command) == command_key_map.end()) {
            throw std::runtime_error("Command " + command + " was not assigned a key.");
        }
    }
}

    Command TerminalHandler::getCommand(char input) {
        if (command_map.find(input) == command_map.end()) {
            return Command::None; 
        }
        return command_map[input];
    }

    // Получение ввода от пользователя
    char TerminalHandler::getInput() {
        char command;
        std::cin >> command;
        return command;
    }

    void TerminalHandler::printMainMenu() {
        std::cout << "Do you want to start a new game or load the previous one?\n";
        std::cout << "[" << command_key_map["New game"] << "] - New game\n";
        std::cout << "[" << command_key_map["Load game"] << "] - Load game\n";
        std::cout << "[" << command_key_map["Exit"] << "] - Exit\n";
        std::cout << "[" << command_key_map["Help"] << "] - Help\n"; 
        std::cout << "Choose the command: ";
    }

    void TerminalHandler::printGameMenu() {
        std::cout << "Player's move\n";
        std::cout << "[" << command_key_map["Attack"] << "] - Attack\n";
        std::cout << "[" << command_key_map["Use ability"] << "] - Use ability\n";
        std::cout << "[" << command_key_map["Save game"] << "] - Save game\n";
        std::cout << "[" << command_key_map["Load game"] << "] - Load game\n";
        std::cout << "[" << command_key_map["Exit"] << "] - Exit\n";
        std::cout << "[" << command_key_map["Help"] << "] - Help\n"; 
        std::cout << "Choose the command: ";
    }

    void TerminalHandler::printHelpMenu() {
        std::cout << "Help Menu:\n";
        std::cout << "[" << command_key_map["Attack"] << "] - Attack\n";
        std::cout << "[" << command_key_map["Use ability"] << "] - Use ability\n";
        std::cout << "[" << command_key_map["Save game"] << "] - Save game\n";
        std::cout << "[" << command_key_map["Load game"] << "] - Load game\n";
        std::cout << "[" << command_key_map["Exit"] << "] - Exit\n";
        std::cout << "[" << command_key_map["Help"] << "] - Help\n";
    }

    std::pair<int, int> TerminalHandler::getAttackCoordinates() {
        std::cout << "Enter the coordinates of the cell you want to attack\n";
        int x, y;
        std::cout << "Enter x and y: ";
        std::cin >> x >> y;
        return {x, y};
    }


