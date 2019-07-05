//
// Created by gianmarco on 01/07/19.
//

#ifndef ASPACEGAME_ASTEROID_H
#define ASPACEGAME_ASTEROID_H

#define APPEARANCE_TIME 5.f
#define FREEZE_TIME 3

#include <SFML/Graphics.hpp>
#include "Animator.h"

class Asteroid {
public:
    Asteroid(float size, float speed);

    Asteroid();

    void move(float dt);

    const sf::Vector2f &getSize() const;

    void setSize(const sf::Vector2f &size);

    float getSpeed() const;

    void setSpeed(float speed);

private:
    float size;
    float speed;
    sf::Sprite sprite;
    Animator *animator = new Animator(sprite);
    float elapsedTime = 0;
    sf::Vector2f initialPosition;
public:
    Animator *getAnimator();

public:
    sf::Sprite &getSprite();

};


#endif //ASPACEGAME_ASTEROID_H
