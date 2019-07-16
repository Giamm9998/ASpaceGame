//
// Created by Fabio Luccioletti on 2019-06-30.
//

#ifndef ASPACEGAME_GAME_H
#define ASPACEGAME_GAME_H

namespace {
    short int const right = 1;
    short int const left = -1;
}

static const float windowWidth = 900;
static const float windowHeight = 675;

static const float achievementFadeDuration = 0.5;
static const float achievementDisappearT = 3;
static const float achievementAnimationT = achievementDisappearT + 0.5;

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
#include "Achievement.h"

class Game {
public:
    Game();

    void run();

    static bool isLegalMove(float x, float origin, short int direction);


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
    bool isChoosingPlayer;
    sf::RectangleShape specialHud;
    sf::RectangleShape specialHudOutline;
    sf::RectangleShape hud;
    sf::RectangleShape hpHud;
    sf::RectangleShape hpHudOutline;
    sf::Text scoreText;
    sf::Text hpText;
    sf::Text specialText;
    sf::Text playerSelection;
    sf::Text playerNames;
    sf::Text gameOver;
    sf::Text leadboard;
    sf::Text insertScore;
    sf::Text nameText;
    sf::Sprite bomberSprite;
    sf::Sprite raptorSprite;
    std::unique_ptr<Background> background;
    std::list<std::unique_ptr<sf::Sprite>> achievementSprites;
    Achievement achievement;
    float achievementDuration;
    sf::Sound achievementSound;

    bool nameEntered = false;

    EntityManager entityManager;

    void createHud();

    void drawBackground();

    void drawPlayer();

    void drawEnemy();

    void drawPowerUp();

    void drawHud();

    void updateAchievement(float time);

    template<typename T>
    void draw(const std::list<std::unique_ptr<T>> &list);

    void insertScoreName();

    void readFile();

    void drawAchievement();
};

#endif //ASPACEGAME_GAME_H
