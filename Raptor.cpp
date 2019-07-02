//
// Created by gianmarco on 30/06/19.
//

#include "Raptor.h"
#include "ResourceManager.h"

Raptor::Raptor() : Player(100, 8, 150) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/RaptorBase.png"));
    primaryCannon.setFireRate(300);
    primaryCannon.setNShots(1);
    primaryCannon.setTracker(false);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 40, &primaryCannon, sf::Vector2f(0, -1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    //TODO establish the right default values
    //TODO initialize the shield

}

void Raptor::useSpecialPower() {

}
