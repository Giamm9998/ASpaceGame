//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include "Cannon.h"
#include "Game.h"

Cannon::Cannon() = default;


void Cannon::setSpaceshipPtr(Spaceship *ptr) {
    Cannon::spaceshipPtr = ptr;
}

void Cannon::setFireRateMultiplier(double multiplier) {
    Cannon::fireRateMultiplier = multiplier;
}

void Cannon::setProjectilePrototype(const Projectile &prototype) {
    Cannon::projectilePrototype = prototype;
}

void Cannon::setTracker(bool track) {
    Cannon::tracker = track;
}

std::unique_ptr<Projectile> Cannon::shoot(const sf::Vector2f &position, float dt) {
    elapsedtime += dt;
    if (elapsedtime >= (1.f / (spaceshipPtr->getFireRate() * fireRateMultiplier))) {
        std::unique_ptr<Projectile> projectile(new Projectile(projectilePrototype));
        projectile->getSprite().setPosition(position);
        elapsedtime = 0;
        return projectile;
    }
    return nullptr;

}


double Cannon::getFireRateMultiplier() const {
    return fireRateMultiplier;
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

void Cannon::setElapsedtime(float time) {
    Cannon::elapsedtime = time;
}

Spaceship *Cannon::getSpaceshipPtr() const {
    return spaceshipPtr;
}

const sf::Vector2f &Cannon::getRelativePosition() const {
    return relativePosition;
}

void Cannon::setLocalRelativePosition(const sf::Vector2f &position) {
    Cannon::relativePosition = position;
}

float Cannon::getStrengthMultiplier() const {
    return strengthMultiplier;
}

void Cannon::setStrengthMultiplier(float multiplier) {
    Cannon::strengthMultiplier = multiplier;
}
