//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_BOSS_H
#define ASPACEGAME_BOSS_H


static const float bossSpawnDuration = 6.7;
static const float bossSpawnHeight = 5;
static const float bossHp = 1000;
static const float bossStrength = 15;
static const float bossSpeed = 50;
static const float bossFireRate = 1;
static const float bossProjectileSpeed = 400;
static const float bossStrengthMult = 1;
static const int bossExplosions = 15;
static const float bossScaleX = 0.5;
static const float bossScaleY = 0.4;
static const float bossBoxSizeX = 1.6;
static const float bossBoxSizeY = 1.4;
static const float bossBombStrengthMult = 3;
static const float bossCannonRelativePosX = 250;
static const float bossMobileFireRateMult = 1.8;
static const float bossTrackerStrengthMult = 1.5;
static const float bossMobileAttackDuration = 5;
static float bossStartPosition = 0;
static float bossFinalPosition = 0;

#include "Enemy.h"
#include <cmath>

class Boss: public Enemy {
public:
    Boss();

    ~Boss() override;

    void move(float time) override;

    std::list<Cannon *> &chooseAttack();

    std::unique_ptr<Projectile> useMobileCannon(float dt, Cannon &cannon);

    std::unique_ptr<Projectile> useTrackerCannon(float dt, Cannon &cannon, const sf::Vector2f &playerPos);

private:
    std::list<Cannon> simpleCannons;
    Cannon mobileCannon;
    Cannon trackerCannon;
    std::list<Cannon> bombCannons;
    float mobileTime = 0;
    double angle = M_PI / 4;
    std::list<Cannon *> currentAttack = {};

    ///TEST METHODS
public:
    std::list<Cannon> &getSimpleCannons() {
        return simpleCannons;
    }

    Cannon &getMobileCannon() {
        return mobileCannon;
    }

    Cannon &getTrackerCannon() {
        return trackerCannon;
    }

    std::list<Cannon> &getBombCannons() {
        return bombCannons;
    }

    float getMobileTime() const {
        return mobileTime;
    }

    double getAngle() const {
        return angle;
    }

    const std::list<Cannon *> &getCurrentAttack() const {
        return currentAttack;
    }
};


#endif //ASPACEGAME_BOSS_H
