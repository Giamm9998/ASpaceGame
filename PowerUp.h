//
// Created by Fabio Luccioletti on 2019-07-01.
//

#ifndef ASPACEGAME_POWERUP_H
#define ASPACEGAME_POWERUP_H


#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animator.h"

static const int speed = 200;

class PowerUp {
public:
    explicit PowerUp(bool special);

    void move(float dt);

    virtual void powerUp(Player *player) = 0;

    sf::Sprite getSprite();

    virtual ~PowerUp();

protected:
    bool special;
    sf::Sprite sprite;
    short int direction = 1;
    Animator *animator = new Animator(sprite);
public:
    Animator *getAnimator();

protected:
    double angle;
};


#endif //ASPACEGAME_POWERUP_H
