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

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include "Spaceship.h"
#include "Enemy.h"
#include "Player.h"
#include "Asteroid.h"
#include "Background.h"
#include "Animator.h"
#include "PowerUp.h"
#include "EntityManager.h"

class Game {
public:
    Game();

    void run();

    static bool isLegalMove(float x, float origin, short int direction);//Todo with sprite


private:
    void processEvents();

    void update(const sf::Time &dt);

    void render();

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    sf::RenderWindow window;
    sf::View view;
    bool isPaused;
    bool isMovingLeft;
    bool isMovingRight;
    bool isShooting;
    bool isUsingSpecial;
    int score;
    sf::RectangleShape specialHud;
    sf::RectangleShape specialHudOutline;
    sf::RectangleShape hud;
    sf::RectangleShape hpHud;
    sf::RectangleShape hpHudOutline;
    sf::Text scoreText;
    sf::Text hpText;
    sf::Text specialText;
    std::unique_ptr<Background> background;

    EntityManager entityManager;

    void createHud();

    void drawBackground();

    void drawPlayer();

    void drawPowerUp();

    void drawHud();

    template<typename T>
    void draw(const std::list<std::unique_ptr<T>> &list);


    //FRIEND_TEST(Game, Functions);

    //FRIEND_TEST(Game, Constructor);
};

#endif //ASPACEGAME_GAME_H
