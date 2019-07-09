//
// Created by gianmarco on 01/07/19.
//

#ifndef ASPACEGAME_ASTEROID_H
#define ASPACEGAME_ASTEROID_H

#define APPEARANCE_TIME 7.f
#define FREEZE_TIME 4
static const int localRadius = 50;

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
