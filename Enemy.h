//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_ENEMY_H
#define ASPACEGAME_ENEMY_H


#include "Spaceship.h"
#include <list>

class Enemy: public Spaceship{

public:
    Enemy(int hp, int strength, int speed);

    void setPosition(float x, float y);

    void move(float time) override;

    const std::list<Enemy>::iterator &getIterator() const;

    void setIterator(const std::list<Enemy>::iterator &iterator);

private:
    std::list<Enemy>::iterator iterator;
};


#endif //ASPACEGAME_ENEMY_H
