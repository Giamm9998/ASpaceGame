//
// Created by Fabio Luccioletti on 2019-06-30.
//

#ifndef ASPACEGAME_CANNON_H
#define ASPACEGAME_CANNON_H


#include "Projectile.h"

class Cannon {
public:
    void shoot();

private:
    int nShots;
    //Spaceship * spaceshipPtr;//TODO make this a smartpointer
    double fireRate;
    Projectile projectilePrototype;
    bool tracker;
};


#endif //ASPACEGAME_CANNON_H
