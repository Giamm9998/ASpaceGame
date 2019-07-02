//
// Created by gianmarco on 30/06/19.
//

#include "Assaulter.h"
#include "ResourceManager.h"

void Assaulter::move(float time) {
    Enemy::move(time);
}

Assaulter::Assaulter() : Enemy(50, 20, 30) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Assaulter.png"));
    primaryCannon.setFireRate(100);
    primaryCannon.setNShots(1);
    primaryCannon.setTracker(true);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 40, &primaryCannon, sf::Vector2f(0, 1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    //TODO establish the right default values
}
