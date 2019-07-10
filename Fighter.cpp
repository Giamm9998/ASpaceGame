//
// Created by gianmarco on 30/06/19.
//

#include "Fighter.h"
#include "ResourceManager.h"

void Fighter::move(float time) {
    Enemy::move(time);
}

Fighter::Fighter() : Enemy(60.f, 10.f, 70.f, 0.3f) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Fighter.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(200, strength * primaryCannon.getStrengthMultiplier());
    primaryCannon.setProjectilePrototype(projectilePrototype);

    externalCannons.resize(2);
    externalCannons[0].setSpaceshipPtr(this);
    externalCannons[0].setLocalRelativePosition(sf::Vector2f(-114, 0));
    externalCannons[0].setProjectilePrototype(projectilePrototype);

    externalCannons[1].setSpaceshipPtr(this);
    externalCannons[1].setLocalRelativePosition(sf::Vector2f(114, 0));
    externalCannons[1].setProjectilePrototype(projectilePrototype);

    boundingBox.setSize(sf::Vector2f(1.5 * sprite.getOrigin().x,
                                     1.5 * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);

    //TODO establish the right default values
}


std::unique_ptr<Projectile> Fighter::useCannon(float dt, Cannon *cannon) {
    return Spaceship::useCannon(dt, cannon);
}

std::vector<Cannon> &Fighter::getExternalCannons() {
    return externalCannons;
}
