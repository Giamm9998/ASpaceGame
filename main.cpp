#include <iostream>
#include "Game.h"


int main() {
    try {
        Game game;
        game.run();
    }
    catch (std::runtime_error &e) {
        std::cerr << "\nEXCEPTION: " << e.what() << std::endl;
    }
    return 0;
}
