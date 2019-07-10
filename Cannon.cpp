//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include "Cannon.h"
#include "Game.h"

Cannon::Cannon() = default;

void Cannon::setFireRateMultiplier(double multiplier) {
    Cannon::fireRateMultiplier = multiplier;
}

void Cannon::setProjectilePrototype(const Projectile &prototype) {
    Cannon::projectilePrototype = prototype;
}

void Cannon::setTracker(bool track) {
    Cannon::tracker = track;
}

std::unique_ptr<Projectile> Cannon::shoot(const sf::Vector2f &position, float dt, float fireRate) {
    elapsedTime += dt;
    if (elapsedTime >= (1.f / (fireRate * fireRateMultiplier))) {
        std::unique_ptr<Projectile> projectile(new Projectile(projectilePrototype));
        projectile->getSprite().setPosition(position);
        elapsedTime = 0;
        return projectile;
    }
    return nullptr;

}


float Cannon::getFireRateMultiplier() const {
    return fireRateMultiplier;
}

Projectile &Cannon::getProjectilePrototype() {
    return projectilePrototype;
}

bool Cannon::isTracker() const {
    return tracker;
}

float Cannon::getElapsedTime() const {
    return elapsedTime;
}

void Cannon::setElapsedTime(float time) {
    Cannon::elapsedTime = time;
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
