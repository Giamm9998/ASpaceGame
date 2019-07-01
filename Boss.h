//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_BOSS_H
#define ASPACEGAME_BOSS_H


#include "Enemy.h"

class Boss: public Enemy {
public:
    void move() override;
    void chooseAttack();
private:
    std::vector<Cannon> cannons;
};


#endif //ASPACEGAME_BOSS_H