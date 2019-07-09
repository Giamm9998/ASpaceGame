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

    std::unique_ptr<Projectile> shoot(sf::Vector2f position, float dt);

    void setSpaceshipPtr(Spaceship *spaceshipPtr);

    void setFireRateMultiplier(double multiplier);

    void setProjectilePrototype(const Projectile &prototype);

    void setTracker(bool track);

    Spaceship *getSpaceshipPtr() const;

    double getFireRateMultiplier() const;

    Projectile &getProjectilePrototype();

    bool isTracker() const;

    float getElapsedtime() const;

    void setElapsedtime(float elapsedtime);

    float getStrengthMultiplier() const;

    const sf::Vector2f &getRelativePosition() const;

    void setRelativePosition(const sf::Vector2f &relativePosition);

    void setFireRateMultiplier1(float fireRateMultiplier);

    void setStrengthMultiplier(float strengthMultiplier);

private:
    Spaceship *spaceshipPtr;//TODO make this a smartpointer
    float fireRateMultiplier = 1;
    float strengthMultiplier = 1;
    Projectile projectilePrototype;
    bool tracker = false;
    float elapsedtime = 0;
    sf::Vector2f relativePosition = sf::Vector2f(0, 0);
};
#endif //ASPACEGAME_CANNON_H
