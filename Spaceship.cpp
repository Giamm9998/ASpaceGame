//
// Created by gianmarco on 30/06/19.
//
#include "Game.h"
#include "Player.h"
#include "Raptor.h"
#include <cmath>
#include "ResourceManager.h"
#include "Spaceship.h"

#define PI 3.14

Spaceship::Spaceship(int hp, int strength, float speed) : hp(hp), strength(strength), speed(speed) {
    sprite.setScale(maxScale, maxScale);
}

int Spaceship::getHp() const {
    return hp;
}

void Spaceship::setHp(int hp) {
    Spaceship::hp = hp;
}

int Spaceship::getStrength() const {
    return strength;
}

void Spaceship::setStrength(int strength) {
    Spaceship::strength = strength;
}

float Spaceship::getSpeed() const {
    return speed;
}

void Spaceship::setSpeed(float speed) {
    Spaceship::speed = speed;
}

sf::Sprite &Spaceship::getSprite() {
    return sprite;
}

Cannon &Spaceship::getPrimaryCannon() {
    return primaryCannon;
}

std::unique_ptr<Projectile> Spaceship::useCannon(float dt, Cannon *cannon) {
    sf::Vector2f position(sprite.getPosition().x + cannon->getRelativePosition().x * sprite.getScale().x,
                          sprite.getPosition().y -
                          (sprite.getGlobalBounds().width / 2) * cos(sprite.getRotation() * PI / 180) +
                          cannon->getRelativePosition().y * sprite.getScale().y);
    return cannon->shoot(position, dt);
}

bool Spaceship::receiveDamage(int damage) {
    receivingDamage = true;
    bool dead = false;
    this->hp -= damage;
    if (hp <= 0)
        dead = true;
    return dead;
}

const sf::RectangleShape &Spaceship::getBoundingBox() const {
    return boundingBox;
}

bool Spaceship::isReceivingDamage() const {
    return receivingDamage;
}

void Spaceship::setReceivingDamage(bool receivingDamage) {
    Spaceship::receivingDamage = receivingDamage;
}

void Spaceship::blink(float time) {
    blinkingTime += time;
    if (blinkingTime <= 0.3)
        sprite.setColor(sf::Color(255, 255, 255, 100));
    if (blinkingTime > 0.3 && blinkingTime <= 0.6)
        sprite.setColor(sf::Color::White);
    if (blinkingTime > 0.6 && blinkingTime < 0.9)
        sprite.setColor(sf::Color(255, 255, 255, 100));
    if (blinkingTime > 0.9 && blinkingTime <= 1.2)
        sprite.setColor(sf::Color::White);
    if (blinkingTime > 1.2) {
        blinkingTime = 0;
        setReceivingDamage(false);
        sprite.setColor(sf::Color::White);
    }
}

Spaceship::~Spaceship() = default;

