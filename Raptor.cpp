//
// Created by gianmarco on 30/06/19.
//

#include "Raptor.h"
#include "ResourceManager.h"

Raptor::Raptor() : Player(100, 8, 150) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/RaptorBase.png"));
    sprite.setOrigin(114, 155);
    primaryCannon.setFireRate(2);
    primaryCannon.setNShots(1);
    primaryCannon.setTracker(false);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 600, sf::Vector2f(0, -1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    primaryCannon.setElapsedtime(0);
    //TODO establish the right default values
    //TODO initialize the shield

}

void Raptor::useSpecialPower() {

}
