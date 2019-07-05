//
// Created by gianmarco on 01/07/19.
//
#include <cmath>
#include "ResourceManager.h"
#include "Asteroid.h"
#include "Randomizer.h"
#include "Animator.h"
#include "Game.h"


float Asteroid::getSpeed() const {
    return speed;
}

void Asteroid::setSpeed(float speed) {
    Asteroid::speed = speed;
}

Asteroid::Asteroid(float size, float speed) : size(size), speed(speed) {}

void Asteroid::move(float dt) {
    elapsedTime += dt;
    if (elapsedTime <= APPEARANCE_TIME) {
        sf::Vector2f deltaScale(size / APPEARANCE_TIME * dt, size / APPEARANCE_TIME * dt);
        sprite.setScale(sprite.getScale() + deltaScale);
        if (elapsedTime >= FREEZE_TIME) {
            float t = elapsedTime - FREEZE_TIME;
            float deltaT = APPEARANCE_TIME - FREEZE_TIME;
            sprite.setPosition(sprite.getPosition().x,
                               initialPosition.y + 0.5 * (speed / (deltaT)) * pow(t, 2));
        }
    } else
        sprite.move(0, speed * dt);
}

Asteroid::Asteroid() {
    auto &rotation = animator->createAnimation("Rotation", "../Texture/Asteroid.png", sf::seconds(1), true);
    int frames = 8;
    int rows = 4;
    int startAnim = 0;
    if (Randomizer::getRandomInt(0, 1))
        startAnim = 128 * 4;
    rotation.addFrames(sf::Vector2i(0, startAnim), sf::Vector2i(128, 128), frames, rows);
    speed = Randomizer::getRandomReal(90, 120);
    size = Randomizer::getRandomReal(0.3, 0.6);
    sprite.setScale(0, 0);
    sf::Vector2f distOrigin(sprite.getLocalBounds().width / (2 * frames),
                            sprite.getLocalBounds().height / (2 * 8));
    initialPosition = Randomizer::getRandomPosition(
            distOrigin.x, windowWidth - distOrigin.x, distOrigin.y, distOrigin.y + 50);
    sprite.setOrigin(distOrigin);
    sprite.setPosition(initialPosition);
}

sf::Sprite &Asteroid::getSprite() {
    return sprite;
}

Animator *Asteroid::getAnimator() {
    return animator;
};
