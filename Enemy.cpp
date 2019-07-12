//
// Created by gianmarco on 30/06/19.
//

#include "Enemy.h"
#include "ResourceManager.h"

void Enemy::move(float time) {
    if (!(Game::isLegalMove(sprite.getPosition().x, sprite.getScale().x * sprite.getOrigin().x, direction)))
        direction = -direction;
    sprite.move(direction * speed * time, 0);
    boundingBox.setPosition(sprite.getPosition());

}

Enemy::Enemy(float hp, float strength, float speed, float fireRate, const Cannon &cannon) : Spaceship(hp, strength,
                                                                                                      speed, fireRate,
                                                                                                      cannon) {
    explosionSound.setBuffer(ResourceManager::getSoundBuffer("../sound/explosion.wav"));
    explosionSound.setVolume(75);
    sprite.setRotation(180.f);
    auto &explosionAnim = animator->createAnimation("Explosion", "../Texture/Explosion.png", sf::seconds(2), false);
    unsigned int frames = 8;
    unsigned int rows = 5;
    explosionAnim.addFrames(sf::Vector2i(0, 0), sf::Vector2i(128, 128), frames, rows);
    explosion.setOrigin(sprite.getLocalBounds().width / (2 * frames), sprite.getLocalBounds().height / (2 * rows));
    explosion.setPosition(sprite.getPosition());
}

void Enemy::setPosition(float x, float y) {
    sprite.setPosition(sf::Vector2f(x, y));
}

void Enemy::setPosition(const sf::Vector2f &pos) {
    sprite.setPosition(pos);
}

void Enemy::blink(float time) {
    blinkingTime += time;
    if (blinkingTime <= enemyBlinkDuration)
        sprite.setColor(sf::Color(230, 130, 130));
    if (blinkingTime > enemyBlinkDuration) {
        blinkingTime = 0;
        setReceivingDamage(false);
        sprite.setColor(sf::Color::White);
    }
}

bool Enemy::die(float time) {

    if (dyingTime == 0) {
        boundingBox.setSize(sf::Vector2f(0, 0));
        explosionSound.play();
    }
    dyingTime += time;
    sprite.setColor(sf::Color(255, 255, 255, 255 - static_cast<int>(255. * dyingTime / dyingDuration)));
    return dyingTime >= dyingDuration;
}

Enemy::~Enemy() = default;
