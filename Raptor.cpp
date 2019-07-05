//
// Created by gianmarco on 30/06/19.
//

#include "Raptor.h"
#include "ResourceManager.h"

Raptor::Raptor() : Player(100, 8, 150) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/RaptorBasic.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    primaryCannon.setFireRate(2);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 600, sf::Vector2f(0, -1), strength, false);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    primaryCannon.setElapsedtime(0);

    shield.setRadius(sprite.getOrigin().y * sprite.getScale().y);
    shield.setOrigin(shield.getRadius(), shield.getRadius());
    shield.setPosition(sprite.getPosition());
    shield.setOutlineColor(sf::Color::Yellow);
    shield.setOutlineThickness(5);
    shield.setFillColor(sf::Color(255, 255, 255, 0));
    //TODO establish the right default values
}

void Raptor::useSpecialPower(float dt) {

}

sf::CircleShape &Raptor::getShield() {
    return shield;
}

void Raptor::move(float time, short int movement) {
    Player::move(time, movement);
    shield.setPosition(sprite.getPosition());
}
