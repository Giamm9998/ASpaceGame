//
// Created by Fabio Luccioletti on 2019-06-30.
//

#ifndef ASPACEGAME_CANNON_H
#define ASPACEGAME_CANNON_H


#include "Projectile.h"
#include <memory>

class Spaceship;

class Cannon {
public:
    Cannon();

    std::unique_ptr<Projectile> shoot(const sf::Vector2f &position, float dt, float fireRate);

    void setFireRateMultiplier(double multiplier);

    void setProjectilePrototype(const Projectile &prototype);

    void setTracker(bool track);

    float getFireRateMultiplier() const;

    Projectile &getProjectilePrototype();

    bool isTracker() const;

    float getElapsedTime() const;

    void setElapsedTime(float time);

    float getStrengthMultiplier() const;

    const sf::Vector2f &getRelativePosition() const;

    void setLocalRelativePosition(const sf::Vector2f &position);

    void setStrengthMultiplier(float multiplier);

private:
    float fireRateMultiplier = 1;
    float strengthMultiplier = 1;
    Projectile projectilePrototype;
    bool tracker = false;
    float elapsedTime = 0;
    sf::Vector2f relativePosition = sf::Vector2f(0, 0);
};
#endif //ASPACEGAME_CANNON_H
