//
// Created by gianmarco on 30/06/19.
//

#include "Enemy.h"

void Enemy::move(float time) {
    sprite.rotate(1.);
}

Enemy::Enemy(int hp, int strength, int speed) : Spaceship(hp, strength, speed) {}

void Enemy::setPosition(float x, float y) {
    sprite.setPosition(sf::Vector2f(x, y));
}

const std::list<Enemy>::iterator &Enemy::getIterator() const {
    return iterator;
}

void Enemy::setIterator(const std::list<Enemy>::iterator &iterator) {
    Enemy::iterator = iterator;
}

void Enemy::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}
