//
// Created by gianmarco on 30/06/19.
//

#include "Raptor.h"
#include "ResourceManager.h"

Raptor::Raptor() : Player(140.f, 10.f, 160.f, 1.8f, Cannon(Projectile(400, 10.f * 1, false))), shieldDuration(5) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/RaptorBasic.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    primaryCannon.setElapsedTime(1.f / (fireRate * primaryCannon.getFireRateMultiplier()));

    laser.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height / 2);

    shield.setRadius(sprite.getOrigin().y * sprite.getScale().y);
    shield.setOrigin(shield.getRadius(), shield.getRadius());
    shield.setPosition(sprite.getPosition());
    shield.setOutlineColor(sf::Color::Yellow);
    shield.setOutlineThickness(5);
    shield.setFillColor(sf::Color(255, 255, 255, 0));

    boundingBox.setSize(sf::Vector2f(1.2f * sprite.getOrigin().x,
                                     1.4f * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y + sprite.getGlobalBounds().height / 8);
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


void Raptor::recharge(float dt, sf::RectangleShape &specialHud) {
    elapsedTime += dt;
    specialHud.setScale(1, elapsedTime / rechargeTime);
    if (elapsedTime > rechargeTime) {
        shield.setScale(1, 1);
        elapsedTime = 0;
        charging = false;
    }
}

float Raptor::getShieldDuration() const {
    return shieldDuration;
}

void Raptor::setShieldDuration(float duration) {
    Raptor::shieldDuration = duration;
}

