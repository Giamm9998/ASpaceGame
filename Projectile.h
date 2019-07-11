//
// Created by gianmarco on 01/07/19.
//

#ifndef ASPACEGAME_PROJECTILE_H
#define ASPACEGAME_PROJECTILE_H


#include <SFML/Graphics.hpp>
#include <memory>

class Projectile {
public:
    Projectile();

    Projectile(const Projectile &original);

    Projectile(float speed, float damage, bool evil = true, const sf::Vector2f &size = sf::Vector2f(0.5, 0.5));

    void move(float time);

    const sf::Vector2f &getSize() const;

    float getSpeed() const;

    const sf::Vector2f &getMovement() const;

    float getDamage() const;

    sf::Sprite &getSprite();

    void setSize(const sf::Vector2f &newSize);

    void setMovement(const sf::Vector2f &newMovement);

    void setDamage(float newDamage);

    bool isEvil() const;

private:
    sf::Vector2f size;
    float speed;
    sf::Sprite sprite;
    sf::Vector2f movement;
    float damage;
    bool evil;
};


#endif //ASPACEGAME_PROJECTILE_H
