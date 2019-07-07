//
// Created by gianmarco on 30/06/19.
//

#include "Enemy.h"
#include "Game.h"

void Enemy::move(float time) {
    if (!(Game::isLegalMove(sprite.getPosition().x, sprite.getScale().x * sprite.getOrigin().x, direction)))
        direction = -direction;
    sprite.move(direction * speed * time, 0);
    boundingBox.setPosition(sprite.getPosition());

}

Enemy::Enemy(int hp, int strength, int speed) : Spaceship(hp, strength, speed) {
    sprite.setRotation(180);
}

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

void Enemy::blink(float time) {
    blinkingTime += time;
    if (blinkingTime <= 0.15)
        sprite.setColor(sf::Color(230, 130, 130));
    if (blinkingTime > 0.15) {
        blinkingTime = 0;
        setReceivingDamage(false);
        sprite.setColor(sf::Color::White);
    }
}
