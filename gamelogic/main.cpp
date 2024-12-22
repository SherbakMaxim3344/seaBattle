#include "../shipsAndMap/ship.h"
#include "../shipsAndMap/shipmanager.h"
#include "../shipsAndMap/map.h"
#include "../Ability/AbilityManager.h"
#include "../holders/holders.h"
#include "../Ability/AbilityResponce.h"
#include "Game.h"
#include "GameController.h"
#include "ConsoleRenderer.h"
#include "GameDisplay.h"
#include "TerminalHandler.h"





int main() {
    Game game;
    std::string commands_filename = "commands.json";
    TerminalHandler handler = TerminalHandler(commands_filename);
    ConsoleRenderer renderer = ConsoleRenderer();
    GameController<TerminalHandler, ConsoleRenderer> controller(game, handler, renderer);

    try {
        controller.start();
    } catch (const IException& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}