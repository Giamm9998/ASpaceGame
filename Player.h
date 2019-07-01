//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_PLAYER_H
#define ASPACEGAME_PLAYER_H

#include "Spaceship.h"

class Player :public Spaceship{
public:
    Player(int hp, int strength, float speed);
    void move() override;
    virtual void useSpecialPower()=0;

};


#endif //ASPACEGAME_PLAYER_H
