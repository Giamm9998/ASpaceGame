//
// Created by Fabio Luccioletti on 2019-06-30.
//

#ifndef ASPACEGAME_GAME_H
#define ASPACEGAME_GAME_H

#include <exception>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include "ResourceManager.h"
#include "Spaceship.h"
#include "Enemy.h"
#include "Player.h"
#include <typeinfo>

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

    Player *player; //todo smart pointer
    std::list<Spaceship *> enemyManager; //todo smart pointer
    std::list<Projectile *> projectileManager; //todo smart pointer

    ResourceManager resourceManager;

};

#endif //ASPACEGAME_GAME_H
