//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_RAPTOR_H
#define ASPACEGAME_RAPTOR_H

static const float rechargeTime = 60;
static const float raptorHp = 150;
static const float raptorStrength = 10;
static const float raptorSpeed = 180;
static const float raptorFireRate = 1.8;
static const float raptorProjectileSpeed = 400;
static const float raptorBoxSizeX = 1.2;
static const float raptorBoxSizeY = 1.4;

#include "Player.h"

class Raptor: public Player{
public:
    Raptor();

    sf::CircleShape &getShield();

    void move(float time, short int movement) override;

    void useShield(float dt, sf::RectangleShape &specialHud);

    void recharge(float dt, sf::RectangleShape &specialHud) override;

    float getShieldDuration() const;

    void setShieldDuration(float duration);

private:
    sf::CircleShape shield;
    float shieldDuration;

};


#endif //ASPACEGAME_RAPTOR_H
