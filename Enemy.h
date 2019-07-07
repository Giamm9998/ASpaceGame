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
    Enemy(int hp, int strength, int speed);

    void setPosition(float x, float y);

    void setPosition(sf::Vector2f pos);

    void move(float time) override;

    const std::list<Enemy>::iterator &getIterator() const;

    void setIterator(const std::list<Enemy>::iterator &iterator);

protected:
    short int direction = right;
    std::list<Enemy>::iterator iterator;
public:
    void blink(float time) override;
};


#endif //ASPACEGAME_ENEMY_H
