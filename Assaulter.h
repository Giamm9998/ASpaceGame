//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_ASSAULTER_H
#define ASPACEGAME_ASSAULTER_H

static const float assaulterFreezeDuration = 5;
static const float assaulterAppearingDuration = 0.4;
static const int assaulterSpawnHeight = 50;
static const float assaulterStrength = 25;
static const float assaulterStrengthMult = 1;
static const float assaulterHp = 100;
static const float assaulterSpeed = 0;
static const float assaulterFireRate = 0.5;
static const float assaulterProjectileSpeed = 300;
static const float assaulterFireRateMult = 1;
static const float assaulterBoxSizeX = 1.5f;
static const float assaulterBoxSizeY = 1.5f;

#include "Enemy.h"

class Assaulter : public Enemy {
public:
    Assaulter();

    void move(float time) override;

    std::unique_ptr<Projectile> useTrackerCannon(float dt, Cannon &cannon, const sf::Vector2f &playerPos);

private:
    bool moved = false;

    ///TEST
public:
    bool isMovedTest() const {
        return moved;
    }
};


#endif //ASPACEGAME_ASSAULTER_H
