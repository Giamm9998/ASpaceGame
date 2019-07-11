//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_BOSS_H
#define ASPACEGAME_BOSS_H


static const float bossSpawnDuration = 5;
static const int bossSpawnHeight = 5;
static float bossStartPosition = 0;
static float bossFinalPosition = 0;

#include "Enemy.h"

class Boss: public Enemy {
public:
    Boss();

    void move(float time) override;
    void chooseAttack();
private:
    std::vector<Cannon> cannons;
};


#endif //ASPACEGAME_BOSS_H
