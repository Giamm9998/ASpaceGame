//
// Created by gianmarco on 01/07/19.
//

#ifndef ASPACEGAME_PROJECTILE_H
#define ASPACEGAME_PROJECTILE_H


#include <SFML/Graphics.hpp>
#include <memory>

class Cannon;

class Projectile {
public:
    Projectile();

    Projectile(const Projectile &original);

    Projectile(sf::Vector2f size, float speed, sf::Vector2f movement, int damage);

    void move(float time);

    const sf::Vector2f &getSize() const;

    float getSpeed() const;

    const sf::Vector2f &getMovement() const;

    int getDamage() const;

    sf::Sprite &getSprite();

    void setSize(const sf::Vector2f &size);

    void setSpeed(float speed);

    void setMovement(const sf::Vector2f &movement);

    void setDamage(int damage);

private:
    sf::Vector2f size;
    float speed;
    sf::Sprite sprite;
    sf::Vector2f movement;
    int damage;
};


#endif //ASPACEGAME_PROJECTILE_H
