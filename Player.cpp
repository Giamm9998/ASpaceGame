//
// Created by gianmarco on 30/06/19.
//

#include "ResourceManager.h"
#include "Raptor.h"
#include "Player.h"
#include "Game.h"
#include "Spaceship.h"


Player::Player(float hp, float strength, float speed, float fireRate) :
        Spaceship(hp, strength, speed, fireRate), charging(false), laserActive(false) {
    sprite.setPosition(static_cast<float>(windowWidth) / 2, windowHeight - PlayerSpawnHeight);

    laser.setSize(sf::Vector2f(sprite.getPosition().y, 10));
    laser.setOrigin(laser.getGlobalBounds().width, laser.getGlobalBounds().height / 2);
    laser.rotate(90.f);
    laser.setFillColor(sf::Color::Red);
}

void Player::move(float time, short int direction) {
    if (Game::isLegalMove(sprite.getPosition().x, sprite.getScale().x * sprite.getOrigin().x, direction)) {
        sprite.move(speed * time * direction, 0);
        boundingBox.move(speed * time * direction, 0);
        laser.move(speed * time * direction, 0);
    }
}


bool Player::isCharging() const {
    return charging;
}

void Player::receiveDamage(float damage) {
    if (!receivingDamage)
        Spaceship::receiveDamage(damage);
}

std::vector<Cannon> &Player::getAuxiliaryCannons() {
    return auxiliaryCannons;
}

bool Player::isLaserActive() const {
    return laserActive;
}

void Player::setLaserActive(bool active) {
    Player::laserActive = active;
}

sf::RectangleShape &Player::getLaser() {
    return laser;
}

void Player::setStrength(float strength) {
    Spaceship::setStrength(strength);
    primaryCannon.getProjectilePrototype().setDamage(strength * primaryCannon.getStrengthMultiplier());
    for (auto &cannon : auxiliaryCannons) {
        cannon.getProjectilePrototype().setDamage(strength * cannon.getStrengthMultiplier());
    }
}

void Player::blink(float time) {
    blinkingTime += time;
    if (blinkingTime <= playerBlinkDuration)
        sprite.setColor(sf::Color(255, 255, 255, 100));
    if (blinkingTime > playerBlinkDuration && blinkingTime <= 2 * playerBlinkDuration)
        sprite.setColor(sf::Color::White);
    if (blinkingTime > 2 * playerBlinkDuration && blinkingTime <= 3 * playerBlinkDuration)
        sprite.setColor(sf::Color(255, 255, 255, 100));
    if (blinkingTime > 3 * playerBlinkDuration && blinkingTime <= 4 * playerBlinkDuration)
        sprite.setColor(sf::Color::White);
    if (blinkingTime > 4 * playerBlinkDuration) {
        blinkingTime = 0;
        setReceivingDamage(false);
        sprite.setColor(sf::Color::White);
    }
}

bool Player::die(float time) {
    return false; //Todo Implement
}

Player::~Player() = default;

