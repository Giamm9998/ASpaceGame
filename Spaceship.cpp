//
// Created by gianmarco on 30/06/19.
//
#include "Game.h"
#include "Player.h"
#include "Raptor.h"
#include <cmath>
#include "ResourceManager.h"
#include "Spaceship.h"

Spaceship::Spaceship(float hp, float strength, float speed, float fireRate) :
        hp(hp), strength(strength), speed(speed), fireRate(fireRate), maxHp(hp) {
    sprite.setScale(maxScale, maxScale);
}

float Spaceship::getHp() const {
    return hp;
}

void Spaceship::setHp(float newHp) {
    Spaceship::hp = newHp;
}

float Spaceship::getStrength() const {
    return strength;
}

void Spaceship::setStrength(float newStrength) {
    Spaceship::strength = newStrength;
}

float Spaceship::getSpeed() const {
    return speed;
}

void Spaceship::setSpeed(float newSpeed) {
    Spaceship::speed = newSpeed;
}

sf::Sprite &Spaceship::getSprite() {
    return sprite;
}

Cannon &Spaceship::getPrimaryCannon() {
    return primaryCannon;
}

std::unique_ptr<Projectile> Spaceship::useCannon(float dt, Cannon &cannon) {
    sf::Vector2f position(sprite.getPosition().x + cannon.getRelativePosition().x * sprite.getScale().x,
                          sprite.getPosition().y -
                          (sprite.getGlobalBounds().width / 2) * cos(sprite.getRotation() * M_PI / 180) +
                          cannon.getRelativePosition().y * sprite.getScale().y);
    return cannon.shoot(position, dt, fireRate);
}

void Spaceship::receiveDamage(float damage) {
    receivingDamage = true;
    this->hp -= damage;
}

const sf::RectangleShape &Spaceship::getBoundingBox() const {
    return boundingBox;
}

bool Spaceship::isReceivingDamage() const {
    return receivingDamage;
}

void Spaceship::setReceivingDamage(bool receiveDamage) {
    Spaceship::receivingDamage = receiveDamage;
}

float Spaceship::getFireRate() const {
    return fireRate;
}

void Spaceship::setFireRate(float rate) {
    Spaceship::fireRate = rate;
}

float Spaceship::getMaxHp() const {
    return maxHp;
}


Spaceship::~Spaceship() = default;

