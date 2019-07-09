//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_ENEMY_H
#define ASPACEGAME_ENEMY_H


#include "Spaceship.h"
#include <list>
#include "Game.h"

class Enemy: public Spaceship{

public:
    Enemy(float hp, float strength, float speed, float fireRate, float maxHp);

    void setPosition(float x, float y);

    void setPosition(sf::Vector2f pos);

    void move(float time) override;

    void blink(float time) override;

protected:
    short int direction = right;
};


#endif //ASPACEGAME_ENEMY_H
