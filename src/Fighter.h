//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_FIGHTER_H
#define ASPACEGAME_FIGHTER_H

static const float fighterSpawnHeight = 60;
static const float fighterHp = 125;
static const float fighterStrength = 20;
static const float fighterSpeed = 70;
static const float fighterFireRate = 0.6;
static const float fighterProjectileSpeed = 250;
static const int fighterExplosions = 5;
static const float fighterBoxSizeX = 1.5;
static const float fighterBoxSizeY = 1.5;
static const float fighterCannonRelativePosition = 114;

#include "Enemy.h"

class Fighter: public Enemy{
public:
    Fighter();

    void move(float time) override;

    std::vector<Cannon> &getExternalCannons();

private:
    std::vector<Cannon> externalCannons;
};


#endif //ASPACEGAME_FIGHTER_H
