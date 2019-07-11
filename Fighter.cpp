//
// Created by gianmarco on 30/06/19.
//

#include "Fighter.h"
#include "ResourceManager.h"

void Fighter::move(float time) {
    Enemy::move(time);
}

Fighter::Fighter() : Enemy(60.f, 10.f, 70.f, 0.3f, Cannon(Projectile(200, 10.f * 1))) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Fighter.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    externalCannons.emplace_back(Cannon(primaryCannon.getProjectilePrototype(), 1, 1, false, sf::Vector2f(-114, 0)));
    externalCannons.emplace_back(Cannon(primaryCannon.getProjectilePrototype(), 1, 1, false, sf::Vector2f(114, 0)));

    boundingBox.setSize(sf::Vector2f(1.5f * sprite.getOrigin().x,
                                     1.5f * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
}

std::vector<Cannon> &Fighter::getExternalCannons() {
    return externalCannons;
}
