//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_ENEMY_H
#define ASPACEGAME_ENEMY_H


static const float enemyBlinkDuration = 0.15;

#include "Spaceship.h"
#include <list>
#include "Game.h"

class Enemy: public Spaceship{

public:
    Enemy(float hp, float strength, float speed, float fireRate);

    ~Enemy() override;

    void setPosition(float x, float y);

    void setPosition(const sf::Vector2f &pos);

    void move(float time) override; //Todo make abstract

    void blink(float time) final;

    bool die(float time) override;

protected:
    short int direction = right;
};


#endif //ASPACEGAME_ENEMY_H
