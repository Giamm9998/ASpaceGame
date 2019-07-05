//
// Created by gianmarco on 01/07/19.
//

#include "Projectile.h"
#include "ResourceManager.h"

void Projectile::move(float time) {
    sprite.move(movement.x * speed * time, movement.y * speed * time);
}

Projectile::Projectile(sf::Vector2f size, float speed, sf::Vector2f movement, int damage, bool evil) : size(
        size), speed(speed), movement(movement), damage(damage), evil(evil) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BasicProjectile.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(size);
}

const sf::Vector2f &Projectile::getSize() const {
    return size;
}

float Projectile::getSpeed() const {
    return speed;
}

const sf::Vector2f &Projectile::getMovement() const {
    return movement;
}

int Projectile::getDamage() const {
    return damage;
}

sf::Sprite &Projectile::getSprite() {
    return sprite;
}

void Projectile::setSize(const sf::Vector2f &size) {
    Projectile::size = size;
}

void Projectile::setSpeed(float speed) {
    Projectile::speed = speed;
}


void Projectile::setMovement(const sf::Vector2f &movement) {
    Projectile::movement = movement;
}

void Projectile::setDamage(int damage) {
    Projectile::damage = damage;
}


Projectile::Projectile(const Projectile &original) :
        size(original.size), speed(original.speed), movement(original.movement),
        damage(original.damage), sprite(original.sprite), evil(original.evil) {}

bool Projectile::isEvil() const {
    return evil;
}

void Projectile::setEvil(bool evil) {
    Projectile::evil = evil;
}


Projectile::Projectile() = default;
