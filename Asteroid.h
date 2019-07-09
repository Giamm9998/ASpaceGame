//
// Created by gianmarco on 01/07/19.
//

#ifndef ASPACEGAME_ASTEROID_H
#define ASPACEGAME_ASTEROID_H

#define ASTEROID_APPEARANCE_DURATION 7.f
#define ASTEROID_FREEZE_DURATION 4

static const int localRadius = 50;
static const float asteroidMinSpeed = 90.f;
static const float asteroidMaxSpeed = 120.f;
static const float asteroidMinSize = 0.3;
static const float asteroidMaxSize = 0.6;
static const int asteroidMaxSpawnHeight = 50;

#include <SFML/Graphics.hpp>
#include "Animator.h"

class Asteroid {

public:

    Asteroid();

    void move(float dt);

    Animator *getAnimator();

    sf::Sprite &getSprite();

    float getDamage() const;

    float getSize() const;

private:

    float damage = 60.f;
    float size;
    float speed;
    sf::Sprite sprite;
    Animator *animator = new Animator(sprite);
    float elapsedTime = 0;
    sf::Vector2f initialPosition;
};


#endif //ASPACEGAME_ASTEROID_H
