//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include "Cannon.h"
#include "Game.h"

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

std::unique_ptr<Projectile> Cannon::shoot(sf::Vector2f position, float dt) {
    elapsedtime += dt;
    if (elapsedtime > (1.f / fireRate)) {
        std::unique_ptr<Projectile> projectile(new Projectile);
        projectile->setSize(projectilePrototype.getSize());
        projectile->setSpeed(projectilePrototype.getSpeed());
        projectile->setDamage(projectilePrototype.getDamage());
        projectile->setMovement(projectilePrototype.getMovement());
        projectile->getSprite().setPosition(position);
        elapsedtime = 0;
        return projectile;
    }
    return nullptr;

}

int Cannon::getNShots() const {
    return nShots;
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

float Cannon::getElapsedtime() const {
    return elapsedtime;
}

void Cannon::setElapsedtime(float elapsedtime) {
    Cannon::elapsedtime = elapsedtime;
}

Spaceship *Cannon::getSpaceshipPtr() const {
    return spaceshipPtr;
}