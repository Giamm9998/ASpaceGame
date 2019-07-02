//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_FIGHTER_H
#define ASPACEGAME_FIGHTER_H


#include "Enemy.h"

class Fighter: public Enemy{
public:
    Fighter();

    void move(float time) override;
};


#endif //ASPACEGAME_FIGHTER_H
