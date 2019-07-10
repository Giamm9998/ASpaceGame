//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_BOSS_H
#define ASPACEGAME_BOSS_H


#define BOSS_SPAWN_DURATION 5.f

static const int bossSpawnHeight = 5;

#include "Enemy.h"

class Boss: public Enemy {
public:
    Boss();

    void move(float time) override;
    void chooseAttack();
private:
    std::vector<Cannon> cannons;
    float startPosition;
    float finalPosition;
};


#endif //ASPACEGAME_BOSS_H
