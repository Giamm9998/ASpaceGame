//
// Created by gianmarco on 01/07/19.
//

#ifndef ASPACEGAME_ASTEROID_H
#define ASPACEGAME_ASTEROID_H

static const float asteroidAppearanceDuration = 7;
static const float asteroidFreezeDuration = 4;
static const int asteroidLocalRadius = 50;
static const float asteroidMinSpeed = 90.f;
static const float asteroidMaxSpeed = 120.f;
static const float asteroidMinSize = 0.3;
static const float asteroidMaxSize = 0.6;
static const float asteroidMaxHp = 50.f;
static const int asteroidMaxSpawnHeight = 50;

#include <SFML/Graphics.hpp>
#include "Animator.h"

class Asteroid {

public:

    Asteroid();

    virtual ~Asteroid();

    void move(float dt);

    Animator *getAnimator() const;

    sf::Sprite &getSprite();

    float getDamage() const;

    float getSize() const;

    void receiveDamage(float damageReceived);

    void blink(float time);

    float getHp() const;

    float getStartingHp() const;

    float getSpeed() const;

    bool isReceivingDamage() const;

    void setReceivingDamage(bool receiveDamage);

    bool die(float time);

private:

    float damage = 60.f;
    float hp;
    float startingHp;
    float size;
    float speed;
    sf::Sprite sprite;
    Animator *animator = new Animator(sprite);
    float elapsedTime = 0;
    float blinkingTime = 0;
    float dyingTime = 0;
    bool receivingDamage = false;
    sf::Vector2f initialPosition;
};


#endif //ASPACEGAME_ASTEROID_H
