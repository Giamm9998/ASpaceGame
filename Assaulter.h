//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_ASSAULTER_H
#define ASPACEGAME_ASSAULTER_H

#define ASSAULTER_FREEZE_DURATION 5.f
#define ASSAULTER_APPEARING_DURATION 0.4

static const int assaulterSpawnHeight = 50;

#include "Enemy.h"

class Assaulter : public Enemy {
public:
    Assaulter();

    void move(float time) override;

    std::unique_ptr<Projectile> useCannon(float dt, Cannon &cannon) override;

    std::unique_ptr<Projectile> useCannon(float dt, Cannon &cannon, sf::Vector2f playerPos);

private:
    bool moved = false;
};


#endif //ASPACEGAME_ASSAULTER_H
