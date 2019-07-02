//
// Created by gianmarco on 01/07/19.
//

#include "Projectile.h"
#include "ResourceManager.h"

void Projectile::move() {}

Projectile::Projectile(sf::Vector2f size, float speed, Cannon *cannonPtr, sf::Vector2f movement, int damage) : size(
        size), speed(speed), cannonPtr(cannonPtr), movement(movement), damage(damage) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BaseProjectile.png"));
}

Projectile::Projectile() = default;
