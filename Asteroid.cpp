//
// Created by gianmarco on 01/07/19.
//
#include "ResourceManager.h"
#include "Asteroid.h"

const sf::Vector2f &Asteroid::getSize() const {
    return size;
}

void Asteroid::setSize(const sf::Vector2f &size) {
    Asteroid::size = size;
}

float Asteroid::getSpeed() const {
    return speed;
}

void Asteroid::setSpeed(float speed) {
    Asteroid::speed = speed;
}

Asteroid::Asteroid(sf::Vector2f size, float speed) : size(size), speed(speed) {
    sprite.setTexture(ResourceManager::getTexture("Asteroid")); //TODO add texture in the folder
}

void Asteroid::move(float dt) {
    sprite.move(0, speed * dt);
}
