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

Kamikaze::Kamikaze() : Enemy(60.f, 30.f, 70.f, 0.8f, Cannon(Projectile(200, 30.f * 1))) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Kamikaze.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    boundingBox.setSize(sf::Vector2f(1.5f * sprite.getOrigin().x,
                                     1.5f * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
}
