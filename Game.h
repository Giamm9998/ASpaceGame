//
// Created by Fabio Luccioletti on 2019-06-30.
//

#ifndef ASPACEGAME_GAME_H
#define ASPACEGAME_GAME_H

namespace {
    short int const right = 1;
    short int const left = -1;
}

static const int windowWidth = 900;
static const int windowHeight = 675;

#include <exception>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include "ResourceManager.h"
#include "Spaceship.h"
#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include "Animator.h"


class Game {
public:
    Game();

    void run();

    static bool isLegalMove(float x, float origin, short int direction);


private:
    void processEvents();

    void update(sf::Time dt);

    void render();

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    sf::RenderWindow window;
    sf::View view;
    bool isPaused;
    bool isMovingLeft;
    bool isMovingRight;
    bool isShooting;
    bool isUsingSpecial;

    Background *background;
    Player *player; //todo smart pointer
    std::list<Spaceship *> enemyManager; //todo smart pointer
    //std::list<Projectile *> projectileManager; //todo smart pointer
    //std::list<std::unique_ptr<Spaceship>> enemyManager;
    std::list<std::unique_ptr<Projectile>> projectileManager;
    //std::unique_ptr<Player> player;
    ResourceManager resourceManager;

    sf::Sprite explosion;
    Animator *animator;

};

#endif //ASPACEGAME_GAME_H
