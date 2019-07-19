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

    float getDamage() const;

    sf::Sprite &getSprite();

    void setMovement(const sf::Vector2f &newMovement);

    void setDamage(float newDamage);

    bool isEvil() const;

private:
    sf::Vector2f size;
    float speed{};
    sf::Sprite sprite;
    sf::Vector2f movement;
    float damage{};
    bool evil{};

    ///TEST
public:
    float getSpeedTest() const {
        return speed;
    }

    const sf::Vector2f &getMovementTest() const {
        return movement;
    }
};


#endif //ASPACEGAME_PROJECTILE_H
