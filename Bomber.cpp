//
// Created by gianmarco on 30/06/19.
//
#include "Bomber.h"
#include "ResourceManager.h"

Bomber::Bomber() : Player(150, 10, 120, 150) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BomberBasic.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    primaryCannon.setFireRate(1);
    primaryCannon.setTracker(false);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 400, sf::Vector2f(0, -1), strength, false);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    secondaryCannon.setSpaceshipPtr(this);
    secondaryCannon.setFireRate(0.5);
    Projectile secondaryProjectilePrototype(sf::Vector2f(0.9, 0.9), 40, sf::Vector2f(0, -1),
                                            strength * 50, false);
    secondaryCannon.setProjectilePrototype(secondaryProjectilePrototype);
    //TODO establish the right default values for both cannons
}


Cannon &Bomber::getSecondaryCannon() {
    return secondaryCannon;
}

std::unique_ptr<Projectile> Bomber::useBomb(float dt) {
    return useCannon(dt, &secondaryCannon);
}

