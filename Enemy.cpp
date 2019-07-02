//
// Created by gianmarco on 30/06/19.
//

#include "Enemy.h"

void Enemy::move() {
    //sprite.rotate(1.);
}

Enemy::Enemy(int hp, int strength, int speed) : Spaceship(hp, strength, speed) {}

void Enemy::setPosition(float x, float y) {
    sprite.setPosition(sf::Vector2f(x, y));
}

const std::list<Enemy, std::__1::allocator<Enemy>>::iterator &Enemy::getIterator() const {
    return iterator;
}

void Enemy::setIterator(const std::list<Enemy, std::__1::allocator<Enemy>>::iterator &iterator) {
    Enemy::iterator = iterator;
}
