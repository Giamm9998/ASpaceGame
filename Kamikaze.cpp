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

Kamikaze::Kamikaze() : Enemy(50.f, 30.f, 30.f, 0.8f) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Kamikaze.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 400, sf::Vector2f(0, 1),
                                   strength * primaryCannon.getStrengthMultiplier());
    primaryCannon.setProjectilePrototype(projectilePrototype);
    //TODO establish the right default values

    boundingBox.setSize(sf::Vector2f(1.5 * sprite.getOrigin().x,
                                     1.5 * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
}
