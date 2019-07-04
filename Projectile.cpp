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
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setScale(size);
}

const sf::Vector2f &Projectile::getSize() const {
    return size;
}

float Projectile::getSpeed() const {
    return speed;
}

Cannon *Projectile::getCannonPtr() {
    return cannonPtr;
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

void Projectile::setMovement(const sf::Vector2f &movement) {
    Projectile::movement = movement;
}

Projectile::Projectile() = default;
