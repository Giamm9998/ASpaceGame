#include <iostream>
#include "Game.h"
#include "ResourceManager.h"

int main() {
    ResourceManager resourceManager;

    try {
        Game game;
        game.run();
    }
    catch (std::runtime_error &e) {
        std::cerr << "\nEXCEPTION: " << e.what() << std::endl;
    }
    return 0;
}
