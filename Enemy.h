//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_ENEMY_H
#define ASPACEGAME_ENEMY_H


#include "Spaceship.h"

class Enemy: public Spaceship{
public:
    void move() override;
};


#endif //ASPACEGAME_ENEMY_H
