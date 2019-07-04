//
// Created by gianmarco on 30/06/19.
//

#include "Fighter.h"
#include "ResourceManager.h"

void Fighter::move(float time) {
    Enemy::move(time);
}

Fighter::Fighter() : Enemy(50, 10, 30) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Fighter.png"));
    sprite.setOrigin(191, 166);
    primaryCannon.setFireRate(0.6);
    primaryCannon.setNShots(3);
    primaryCannon.setTracker(false);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 200, sf::Vector2f(0, 1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    //TODO establish the right default values
}


std::unique_ptr<Projectile> Fighter::useCannon(float dt, Cannon *cannon) {
    return Spaceship::useCannon(dt, cannon);
}
