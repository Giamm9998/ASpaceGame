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

    virtual ~Boss();

    void move(float time) override;

    std::list<Cannon *> &chooseAttack();

    std::unique_ptr<Projectile> useMobileCannon(float dt, Cannon &cannon);

    std::unique_ptr<Projectile> useCannon(float dt, Cannon &cannon, const sf::Vector2f &playerPos);

    std::unique_ptr<Projectile> useCannon(float dt, Cannon &cannon) override;

private:
    std::list<Cannon *> simpleCannons;
    Cannon *mobileCannon;
    Cannon *trackerCannon;
    std::list<Cannon *> bombCannon;
    float mobileTime = 0;
    double angle = M_PI / 4;
    std::list<Cannon *> currentAttack = {};
};


#endif //ASPACEGAME_BOSS_H
