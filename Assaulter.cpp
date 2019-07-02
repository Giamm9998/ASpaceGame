//
// Created by gianmarco on 30/06/19.
//

#include "Assaulter.h"
#include "ResourceManager.h"

void Assaulter::move(float time) {
    elapsedTime += time;
    auto scale = sprite.getScale().x;
    if (elapsedTime >= 1 && elapsedTime < 2 && scale >= 0.01) {
        sprite.setScale(scale - (1 * time), scale - (1 * time));
    } else if (elapsedTime >= 2 && scale <= 0.35)
        sprite.setScale(scale + (1 * time), scale + (1 * time));
    else if (elapsedTime >= 3)
        elapsedTime = 0;

}

Assaulter::Assaulter() : Enemy(50, 20, 30), elapsedTime(0) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Assaulter.png"));
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    primaryCannon.setFireRate(100);
    primaryCannon.setNShots(1);
    primaryCannon.setTracker(true);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 40, &primaryCannon, sf::Vector2f(0, 1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    //TODO establish the right default values
}
