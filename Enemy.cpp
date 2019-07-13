//
// Created by gianmarco on 30/06/19.
//

#include "Enemy.h"
#include "Functions.h"

void Enemy::move(float time) {
    if (!(Game::isLegalMove(sprite.getPosition().x, sprite.getScale().x * sprite.getOrigin().x, direction)))
        direction = -direction;
    sprite.move(direction * speed * time, 0);
    boundingBox.setPosition(sprite.getPosition());

}

Enemy::Enemy(float hp, float strength, float speed, float fireRate, const Cannon &cannon, int explosionNum)
        : Spaceship(hp, strength, speed, fireRate, cannon), explosionNum(explosionNum) {
    sprite.setRotation(180.f);

    unsigned int frames = 8;
    unsigned int rows = 5;
    for (int i = 0; i < this->explosionNum; i++) {
        explosions.emplace_back();
        explosions.back().setScale(sf::Vector2f(1, 1) * getRandomReal(0.5, 1.2));
        animators.emplace_back(new Animator(explosions.back()));
        std::string textureName = getRandomInt(0, 1) ? "../Texture/Explosion.png" : "../Texture/Explosion1.png";
        auto &explosionAnim = animators.back()->createAnimation("Explosion", textureName, sf::seconds(
                explosionDuration), false);
        explosionAnim.addFrames(sf::Vector2i(0, 0), sf::Vector2i(128, 128), frames, rows);
        explosions.back().setOrigin(explosions.back().getLocalBounds().width / (2 * frames),
                                    explosions.back().getLocalBounds().height / (2 * rows));
        animators.back()->update(0);
    }
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
        for (auto &explosion : explosions)
            explosion.setPosition(getRandomPosition(sprite.getGlobalBounds().left,
                                                    sprite.getGlobalBounds().left + sprite.getGlobalBounds().width,
                                                    sprite.getGlobalBounds().top,
                                                    sprite.getGlobalBounds().top + sprite.getGlobalBounds().height));
        boundingBox.setSize(sf::Vector2f(0, 0));
    }
    int i = 0;
    for (auto &animator : animators) {
        animator->update(time, ((dyingDuration - explosionDuration) / explosionNum) * i++);
    }
    dyingTime += time;
    sprite.setColor(sf::Color(255, 255, 255, 255 - static_cast<int>(255. * dyingTime / dyingDuration)));
    return dyingTime >= dyingDuration;
}

const std::list<sf::Sprite> &Enemy::getExplosions() const {
    return explosions;
}

Enemy::~Enemy() = default;
