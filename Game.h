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
#include "Asteroid.h"
#include "Background.h"
#include "Animator.h"
#include "PowerUp.h"


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
    sf::RectangleShape specialHud;
    Background *background;
    Player *player; //todo smart pointer
    std::list<Spaceship *> enemyManager; //todo smart pointer
    //std::list<std::unique_ptr<Spaceship>> enemyManager;
    std::list<std::unique_ptr<Projectile>> projectileManager;
    //std::unique_ptr<Player> player;
    std::list<std::unique_ptr<Asteroid>> asteroidManager;
    std::unique_ptr<PowerUp> powerUp;
    ResourceManager resourceManager;

    void drawAsteroids();

    void drawBackground();

    void drawEnemies();

    void drawPlayer();

    void drawProjectiles();

    void updateEnemies(float time);

    void updatePlayer(float time);

    void updateProjectiles(float time);

    void updatePowerUp(sf::Time dt);

    void updateAsteroids(sf::Time dt);

    void checkForProjectileCollisions(std::list<std::unique_ptr<Projectile>>::iterator projectileIter);

    void emplaceProj(std::unique_ptr<Projectile> uniquePtr);

    bool isOutOfSigth(const sf::Sprite &sprite) const;

    void checkForAsteroidsCollisions(std::list<std::unique_ptr<Asteroid>>::iterator asteroidIter);

    void drawPowerUp();

    float dist(const sf::Vector2f &pointA, const sf::Vector2f &pointB);
};

#endif //ASPACEGAME_GAME_H
