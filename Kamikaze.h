//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_KAMIKAZE_H
#define ASPACEGAME_KAMIKAZE_H

static const float kamikazeFreezeDuration = 2;
static const float kamikazeMoveDuration = 0.2;
static const float kamikazeMaxHeight = 120;
static const float kamikazeSpanWidth = 150;
static const float kamikazeHp = 60;
static const float kamikazeStregth = 30;
static const float kamikazeSpeed = 70;
static const float kamikazeFireRate = 0.8;
static const float kamikazeProjectileSpeed = 200;

#include "Enemy.h"

class Kamikaze: public Enemy {
public:
    Kamikaze();

    void move(float time) override;
    void attract();
    void explode();

private:
    sf::Vector2f movement;
};


#endif //ASPACEGAME_KAMIKAZE_H
