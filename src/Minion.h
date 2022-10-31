//
// Created by Fabio Luccioletti on 2019-07-02.
//

#ifndef ASPACEGAME_MINION_H
#define ASPACEGAME_MINION_H


static const float minionFreezeDuration = 1;
static const float minionSpawnHeight = 160;
static const float minionHp = 75;
static const float minionStrength = 15;
static const float minionSpeed = 100;
static const float minionFireRate = 0.5;
static const float minionProjectileSpeed = 250;
static const float minionBoxSizeX = 1.5;
static const float minionBoxSizeY = 1.5;

#include "Enemy.h"
#include "Game.h"

class Minion : public Enemy {
public:
    Minion();

    void move(float time) override;
};

#endif //ASPACEGAME_MINION_H
