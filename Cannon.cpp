//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include "Cannon.h"
#include "Game.h"

Cannon::Cannon() = default;


void Cannon::setSpaceshipPtr(Spaceship *spaceshipPtr) {
    Cannon::spaceshipPtr = spaceshipPtr;
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

std::unique_ptr<Projectile> Cannon::shoot(sf::Vector2f position, float dt) {
    elapsedtime += dt;
    if (elapsedtime > (1.f / (spaceshipPtr->getFireRate() * fireRateMultiplier))) {
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

void Cannon::setElapsedtime(float elapsedtime) {
    Cannon::elapsedtime = elapsedtime;
}

Spaceship *Cannon::getSpaceshipPtr() const {
    return spaceshipPtr;
}

const sf::Vector2f &Cannon::getRelativePosition() const {
    return relativePosition;
}

void Cannon::setRelativePosition(const sf::Vector2f &relativePosition) {
    Cannon::relativePosition = relativePosition;
}

float Cannon::getStrengthMultiplier() const {
    return strengthMultiplier;
}

void Cannon::setFireRateMultiplier1(float fireRateMultiplier) {
    Cannon::fireRateMultiplier = fireRateMultiplier;
}

void Cannon::setStrengthMultiplier(float strengthMultiplier) {
    Cannon::strengthMultiplier = strengthMultiplier;
}
