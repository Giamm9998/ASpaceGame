//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_ASSAULTER_H
#define ASPACEGAME_ASSAULTER_H

static const float assaulterFreezeDuration = 5;
static const float assaulterAppearingDuration = 0.4;
static const int assaulterSpawnHeight = 50;
static const float assaulterStrength = 20;
static const float assaulterStrengthMult = 1;

#include "Enemy.h"

class Assaulter : public Enemy {
public:
    Assaulter();

    void move(float time) override;

    std::unique_ptr<Projectile> useCannon(float dt, Cannon &cannon) override;

    std::unique_ptr<Projectile> useCannon(float dt, Cannon &cannon, const sf::Vector2f &playerPos);

private:
    bool moved = false;
};


#endif //ASPACEGAME_ASSAULTER_H
