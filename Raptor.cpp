//
// Created by gianmarco on 30/06/19.
//

#include "Raptor.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Spaceship.h"

Raptor::Raptor() : Player(100, 8, 150, 100), shieldDuration(5), charging(false) {
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

    boundingBox.setSize(sf::Vector2f(1.2 * sprite.getOrigin().x * sprite.getScale().x,
                                     1.4 * sprite.getOrigin().y * sprite.getScale().y));
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y + sprite.getGlobalBounds().height / 8);
    boundingBox.setFillColor(sf::Color(255, 255, 255, 255));


    //TODO establish the right default values
}

void Raptor::useShield(float dt, sf::RectangleShape &specialHud) {
    elapsedTime += dt;
    specialHud.setScale(1, 1 - elapsedTime / shieldDuration);
    if (elapsedTime >= shieldDuration) {
        charging = true;
        elapsedTime = 0;
        shield.setScale(0, 0);
    }

}

sf::CircleShape &Raptor::getShield() {
    return shield;
}

void Raptor::move(float time, short int movement) {
    Player::move(time, movement);
    shield.setPosition(sprite.getPosition());
}

bool Raptor::isCharging() const {
    return charging;
}

void Raptor::recharge(float dt, sf::RectangleShape &specialHud) {
    elapsedTime += dt;
    specialHud.setScale(1, elapsedTime / rechargeTime);
    if (elapsedTime > rechargeTime) {
        shield.setScale(1, 1);
        elapsedTime = 0;
        charging = false;
    }
}

