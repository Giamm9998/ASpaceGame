//
// Created by gianmarco on 01/07/19.
//

#include "Projectile.h"
#include "ResourceManager.h"

void Projectile::move(float time) {
    sprite.move(movement.x * speed * time, movement.y * speed * time);
}

Projectile::Projectile(sf::Vector2f size, float speed, Cannon *cannonPtr, sf::Vector2f movement, int damage) : size(
        size), speed(speed), cannonPtr(cannonPtr), movement(movement), damage(damage) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BaseProjectile.png"));
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

void Projectile::setCannonPtr(Cannon *cannonPtr) {
    Projectile::cannonPtr = cannonPtr;
}

Cannon *Projectile::getCannonPtr() {
    return cannonPtr;
}



Projectile::Projectile() = default;
