//
// Created by Fabio Luccioletti on 2019-06-30.
//

#ifndef ASPACEGAME_CANNON_H
#define ASPACEGAME_CANNON_H


#include "Projectile.h"

class Spaceship;

class Cannon {
public:
    Cannon();

    Projectile *shoot(float dt);

    void setNShots(int nShots);

    void setSpaceshipPtr(Spaceship *spaceshipPtr);

    void setFireRate(double fireRate);

    void setProjectilePrototype(const Projectile &projectilePrototype);

    void setTracker(bool tracker);

    int getNShots() const;

    Spaceship *getSpaceshipPtr() const;

    double getFireRate() const;

    Projectile &getProjectilePrototype();

    bool isTracker() const;

    float getElapsedtime() const;

    void setElapsedtime(float elapsedtime);

private:
    int nShots;
    Spaceship *spaceshipPtr;//TODO make this a smartpointer
    double fireRate;
    Projectile projectilePrototype;
    bool tracker;
    float elapsedtime;
};


#endif //ASPACEGAME_CANNON_H
