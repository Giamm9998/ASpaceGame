//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include "Cannon.h"

Cannon::Cannon() = default;

void Cannon::setNShots(int nShots) {
    Cannon::nShots = nShots;
}

void Cannon::setSpaceshipPtr(Spaceship *spaceshipPtr) {
    Cannon::spaceshipPtr = spaceshipPtr;
}

void Cannon::setFireRate(double fireRate) {
    Cannon::fireRate = fireRate;
}

void Cannon::setProjectilePrototype(const Projectile &projectilePrototype) {
    Cannon::projectilePrototype = projectilePrototype;
}

void Cannon::setTracker(bool tracker) {
    Cannon::tracker = tracker;
}

void Cannon::shoot() {}

int Cannon::getNShots() const {
    return nShots;
}

Spaceship *Cannon::getSpaceshipPtr() const {
    return spaceshipPtr;
}

double Cannon::getFireRate() const {
    return fireRate;
}

Projectile &Cannon::getProjectilePrototype() {
    return projectilePrototype;
}

bool Cannon::isTracker() const {
    return tracker;
}


