//
// Created by gianmarco on 01/07/19.
//

#ifndef ASPACEGAME_ASTEROID_H
#define ASPACEGAME_ASTEROID_H

#include <SFML/Graphics.hpp>

class Asteroid {
public:
    Asteroid(sf::Vector2f size, float speed);

    void move(float dt);

    const sf::Vector2f &getSize() const;

    void setSize(const sf::Vector2f &size);

    float getSpeed() const;

    void setSpeed(float speed);

private:
    sf::Vector2f size;
    float speed;
    sf::Sprite sprite;
};


#endif //ASPACEGAME_ASTEROID_H
