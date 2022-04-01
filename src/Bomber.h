//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_BOMBER_H
#define ASPACEGAME_BOMBER_H


static const float bomberStrength = 15;
static const float bomberSecondaryStrengthMult = 3;
static const float bomberHp = 250;
static const float bomberSpeed = 180;
static const float bomberFireRate = 1.2;
static const float bomberProjectileSpeed = 400;
static const float bombSpeed = 250;
static const float bombSize = 0.9;
static const float bomberSecondaryFireRateMult = 0.2;

static const float bomberBoxSizeX = 1.2f;

static const float bomberBoxSizeY = 1.3f;

#include "Player.h"

class Bomber: public Player {
public:
    Bomber();

    std::unique_ptr<Projectile> useBomb(sf::RectangleShape &specialHud);

    Cannon &getSecondaryCannon();

    void recharge(float dt, sf::RectangleShape &specialHud) override;


private:
    Cannon secondaryCannon;
};


#endif //ASPACEGAME_BOMBER_H
