//
// Created by gianmarco on 30/06/19.
//

#include "ResourceManager.h"
#include "Raptor.h"
#include "Game.h"
#include "Functions.h"


Player::Player(float hp, float strength, float speed, float fireRate, const Cannon &cannon) :
        Spaceship(hp, strength, speed, fireRate, cannon, 5), charging(false), laserActive(false) {
    sprite.setPosition(static_cast<float>(windowWidth) / 2, windowHeight - PlayerSpawnHeight);

    auto &laserAnim = laserAnimator->createAnimation("Laser", "../Texture/Laser.png", sf::seconds(1), true);
    unsigned int frames = 12;
    laserAnim.addFrames(sf::Vector2i(0, 0), sf::Vector2i(29, 700), frames);
    laser.setOrigin(laser.getGlobalBounds().width / (2 * frames), laser.getGlobalBounds().height);
    laserSound.setBuffer(ResourceManager::getSoundBuffer("../sound/laser.wav"));
    laserSound.setLoop(true);
    laserSound.setVolume(50);
    powerUpSound.setBuffer(ResourceManager::getSoundBuffer("../sound/powerUp.wav"));
}

void Player::move(float time, short int direction) {
    if (Game::isLegalMove(sprite.getPosition().x, sprite.getScale().x * sprite.getOrigin().x, direction)) {
        sprite.move(speed * time * direction, 0);
        boundingBox.move(speed * time * direction, 0);
        laser.move(speed * time * direction, 0);
    }
}


bool Player::isCharging() const {
    return charging;
}

void Player::receiveDamage(float damage) {
    if (!receivingDamage)
        Spaceship::receiveDamage(damage);
}

std::vector<Cannon> &Player::getAuxiliaryCannons() {
    return auxiliaryCannons;
}

bool Player::isLaserActive() const {
    return laserActive;
}

void Player::setLaserActive(bool active) {
    Player::laserActive = active;
    laserAnimator->update(0);
}

sf::Sprite &Player::getLaser() {
    return laser;
}

void Player::setStrength(float strength) {
    Spaceship::setStrength(strength);
    primaryCannon.getProjectilePrototype().setDamage(strength * primaryCannon.getStrengthMultiplier());
    for (auto &cannon : auxiliaryCannons) {
        cannon.getProjectilePrototype().setDamage(strength * cannon.getStrengthMultiplier());
    }
}

void Player::blink(float time) {
    blinkingTime += time;
    if (blinkingTime <= playerBlinkDuration)
        sprite.setColor(sf::Color(255, 255, 255, 100));
    if (blinkingTime > playerBlinkDuration && blinkingTime <= 2 * playerBlinkDuration)
        sprite.setColor(sf::Color::White);
    if (blinkingTime > 2 * playerBlinkDuration && blinkingTime <= 3 * playerBlinkDuration)
        sprite.setColor(sf::Color(255, 255, 255, 100));
    if (blinkingTime > 3 * playerBlinkDuration && blinkingTime <= 4 * playerBlinkDuration)
        sprite.setColor(sf::Color::White);
    if (blinkingTime > 4 * playerBlinkDuration) {
        blinkingTime = 0;
        setReceivingDamage(false);
        sprite.setColor(sf::Color::White);
    }
}

bool Player::die(float time) {
    if (dyingTime == 0) {
        movable = false;
        explosionSound.play(); //todo play with every explosion
        for (auto &explosion : explosions)
            explosion.setPosition(getRandomPosition(sprite.getGlobalBounds().left,
                                                    sprite.getGlobalBounds().left + sprite.getGlobalBounds().width,
                                                    sprite.getGlobalBounds().top,
                                                    sprite.getGlobalBounds().top + sprite.getGlobalBounds().height));
    }
    int i = 0;
    for (auto &animator : animators) {
        animator->update(time, ((dyingDuration - explosionDuration) / explosionNum) * i++);
    }
    dyingTime += time;
    sprite.setColor(sf::Color(255, 255, 255, 255 - static_cast<int>(255. * dyingTime / dyingDuration)));
    return dyingTime >= dyingDuration;
}

Animator *Player::getLaserAnimator() const {
    return laserAnimator;
}

sf::Sound &Player::getLaserSound() {
    return laserSound;
}

sf::Sound &Player::getPowerUpSound() {
    return powerUpSound;
}

Player::~Player() {
    delete laserAnimator;
}

bool Player::isMovable() const {
    return movable;
}

void Player::setMovable(bool move) {
    Player::movable = move;
}

