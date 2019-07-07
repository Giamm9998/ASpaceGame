//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_PLAYER_H
#define ASPACEGAME_PLAYER_H

#include "Spaceship.h"

class Player :public Spaceship{
public:
    Player(int hp, int strength, float speed, int maxHp);

    void move(float time) override {};

    virtual void move(float time, short int movement);

    int getMaxHp() const;

    bool isCharging() const;

    bool receiveDamage(int damage) override;

protected:
    int maxHp;
    bool charging;

};


#endif //ASPACEGAME_PLAYER_H
