#include <utility>

//
// Created by gianmarco on 30/06/19.
//
#include "Game.h"
#include <cmath>
#include "ResourceManager.h"
#include "Functions.h"

Spaceship::Spaceship(float hp, float strength, float speed, float fireRate, Cannon cannon, int explosion) :
        hp(hp), strength(strength), speed(speed), fireRate(fireRate), maxHp(hp), primaryCannon(std::move(cannon)),
        explosionNum(explosion) {
    sprite.setScale(maxScale, maxScale);

    explosionSound.setBuffer(ResourceManager::getSoundBuffer("../sound/explosion.wav"));
    explosionSound.setVolume(50);
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

std::unique_ptr<Projectile> Spaceship::useCannon(float dt, Cannon &cannon) {
    sf::Vector2f position(sprite.getPosition().x + cannon.getLocalRelativePosition().x * sprite.getScale().x,
                          sprite.getPosition().y -
                          (sprite.getGlobalBounds().height / 2) * cos(sprite.getRotation() * M_PI / 180) +
                          cannon.getLocalRelativePosition().y * sprite.getScale().y);
    return cannon.shoot(position, dt, fireRate);
}

float Spaceship::getHp() const {
    return hp;
}

void Spaceship::setHp(float newHp) {
    Spaceship::hp = newHp;
}

float Spaceship::getStrength() const {
    return strength;
}

void Spaceship::setStrength(float newStrength) {
    Spaceship::strength = newStrength;
}

float Spaceship::getSpeed() const {
    return speed;
}

void Spaceship::setSpeed(float newSpeed) {
    Spaceship::speed = newSpeed;
}

sf::Sprite &Spaceship::getSprite() {
    return sprite;
}

Cannon &Spaceship::getPrimaryCannon() {
    return primaryCannon;
}

void Spaceship::receiveDamage(float damage) {
    receivingDamage = true;
    this->hp -= damage;
}

sf::RectangleShape &Spaceship::getBoundingBox() {
    return boundingBox;
}

bool Spaceship::isReceivingDamage() const {
    return receivingDamage;
}

void Spaceship::setReceivingDamage(bool receiveDamage) {
    Spaceship::receivingDamage = receiveDamage;
}

float Spaceship::getFireRate() const {
    return fireRate;
}
float Spaceship::getMaxHp() const {
    return maxHp;
}

float Spaceship::getDyingTime() const {
    return dyingTime;
}

const std::list<sf::Sprite> &Spaceship::getExplosions() const {
    return explosions;
}

float Spaceship::getElapsedTime() const {
    return elapsedTime;
}

void Spaceship::setElapsedTime(float time) {
    Spaceship::elapsedTime = time;
}


Spaceship::~Spaceship() = default;

