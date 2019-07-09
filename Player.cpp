//
// Created by gianmarco on 30/06/19.
//

#include "ResourceManager.h"
#include "Raptor.h"
#include "Player.h"
#include "Game.h"
#include "Spaceship.h"


Player::Player(float hp, float strength, float speed, float fireRate, float maxHp) : Spaceship(hp, strength, speed,
                                                                                               fireRate, maxHp),
                                                                                     charging(false),
                                                                                     laserActive(false) {
    sprite.setPosition(static_cast<float>(windowWidth) / 2,
                       windowHeight - 80); //todo set position not based on constants
    laser.setSize(sf::Vector2f(windowHeight - 100, 10));
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

void Player::setLaserActive(bool laserActive) {
    Player::laserActive = laserActive;
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
