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
#include <cmath>

class Boss: public Enemy {
public:
    Boss();

    void move(float time) override;
    void chooseAttack();

    std::unique_ptr<Projectile> useCannon(float dt, Cannon &cannon) override;

    std::unique_ptr<Projectile> useCannon(float dt, Cannon &cannon, const sf::Vector2f &playerPos);


    std::list<Cannon> &getSimpleCannons();

    Cannon &getMobileCannon();

    Cannon &getTrackerCannon();

    std::list<Cannon> &getBombcannon();

private:
    std::list<Cannon> simpleCannons;
    Cannon mobileCannon;
    Cannon trackerCannon;
    std::list<Cannon> bombcannon;
    double angle = M_PI / 4;
};


#endif //ASPACEGAME_BOSS_H
