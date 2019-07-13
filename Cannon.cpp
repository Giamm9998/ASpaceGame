//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include "Cannon.h"
#include "Game.h"

Cannon::Cannon(const Projectile &projectilePrototype, float fireRateMultiplier, float strengthMultiplier,
               bool tracker, const sf::Vector2f &relativePosition) :
        fireRateMultiplier(fireRateMultiplier), strengthMultiplier(strengthMultiplier),
        tracker(tracker), localRelativePosition(relativePosition), projectilePrototype(projectilePrototype) {}

void Cannon::setFireRateMultiplier(double multiplier) {
    Cannon::fireRateMultiplier = multiplier;
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

const sf::Vector2f &Cannon::getLocalRelativePosition() const {
    return localRelativePosition;
}

void Cannon::setLocalRelativePosition(const sf::Vector2f &position) {
    Cannon::localRelativePosition = position;
}

float Cannon::getStrengthMultiplier() const {
    return strengthMultiplier;
}

void Cannon::setTracker(bool tracker) {
    Cannon::tracker = tracker;
}
