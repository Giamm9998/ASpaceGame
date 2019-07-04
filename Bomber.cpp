//
// Created by gianmarco on 30/06/19.
//
#include "Bomber.h"
#include "ResourceManager.h"

Bomber::Bomber() : Player(150, 10, 120) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BomberBase.png"));
    sprite.setOrigin(140, 161);
    primaryCannon.setFireRate(1);
    primaryCannon.setTracker(false);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 400, sf::Vector2f(0, -1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    secondaryCannon.setSpaceshipPtr(this);
    secondaryCannon.setFireRate(0.5);
    Projectile secondaryProjectilePrototype(sf::Vector2f(0.9, 0.9), 40, sf::Vector2f(0, -1),
                                            strength * 3);
    secondaryCannon.setProjectilePrototype(secondaryProjectilePrototype);
    //TODO establish the right default values for both cannons
}


Cannon &Bomber::getSecondaryCannon() {
    return secondaryCannon;
}

std::unique_ptr<Projectile> Bomber::useBomb(float dt) {
    return useCannon(dt, &secondaryCannon);
}

