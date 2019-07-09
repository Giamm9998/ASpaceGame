//
// Created by gianmarco on 01/07/19.
//

#include "Projectile.h"
#include "ResourceManager.h"

void Projectile::move(float time) {
    sprite.move(movement.x * speed * time, movement.y * speed * time);
}

Projectile::Projectile() = default;

Projectile::Projectile(float speed, float damage, bool evil, sf::Vector2f size) : size(
        size), speed(speed), damage(damage), evil(evil) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BasicProjectile.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(size);
    movement = sf::Vector2f(0, evil ? 1 : -1);
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

float Projectile::getDamage() const {
    return damage;
}

sf::Sprite &Projectile::getSprite() {
    return sprite;
}

void Projectile::setSize(const sf::Vector2f &newSize) {
    Projectile::size = newSize;
}

void Projectile::setMovement(const sf::Vector2f &newMovement) {
    Projectile::movement = newMovement;
}

Projectile::Projectile(const Projectile &original) = default;

bool Projectile::isEvil() const {
    return evil;
}

void Projectile::setDamage(float newDamage) {
    Projectile::damage = newDamage;
}

