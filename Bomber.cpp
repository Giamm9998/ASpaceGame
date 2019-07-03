//
// Created by gianmarco on 30/06/19.
//
#include "Bomber.h"
#include "ResourceManager.h"

Bomber::Bomber() : Player(150, 10, 120) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BomberBase.png"));
    sprite.setOrigin(140, 161);
    primaryCannon.setFireRate(200);
    primaryCannon.setNShots(1);
    primaryCannon.setTracker(false);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 40, &primaryCannon, sf::Vector2f(0, -1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    secondaryCannon.setSpaceshipPtr(this);
    secondaryCannon.setTracker(false);
    secondaryCannon.setNShots(1);
    secondaryCannon.setFireRate(100);
    Projectile secondaryProjectilePrototype(sf::Vector2f(0.9, 0.9), 40, &secondaryCannon, sf::Vector2f(0, -1),
                                            strength * 3);
    secondaryCannon.setProjectilePrototype(secondaryProjectilePrototype);
    //TODO establish the right default values for both cannons
}

void Bomber::useSpecialPower() {

}

Cannon &Bomber::getSecondaryCannon() {
    return secondaryCannon;
}
