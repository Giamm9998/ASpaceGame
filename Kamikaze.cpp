//
// Created by gianmarco on 30/06/19.
//

#include "Kamikaze.h"
#include "ResourceManager.h"

void Kamikaze::move(float time) {
    Enemy::move(time);
}

void Kamikaze::attract() {}

void Kamikaze::explode() {}

Kamikaze::Kamikaze() : Enemy(50, 30, 30) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Kamikaze.png"));
    sprite.setOrigin(109, 150);
    primaryCannon.setFireRate(50);
    primaryCannon.setNShots(1);
    primaryCannon.setTracker(false);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 80, &primaryCannon, sf::Vector2f(0, 1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    //TODO establish the right default values
}
