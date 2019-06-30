//
// Created by Fabio Luccioletti on 2019-06-30.
//

#ifndef ASPACEGAME_GAME_H
#define ASPACEGAME_GAME_H

#include <exception>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game {
public:
    Game();

    void run();


private:
    void processEvents();

    void update(sf::Time dt);

    void render();

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    void backScroll();

    sf::RenderWindow window;
    sf::View view;
    bool isPaused;
    bool isMovingLeft;
    bool isMovingRight;

};


#endif //ASPACEGAME_GAME_H
