//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_SPACESHIP_H
#define ASPACEGAME_SPACESHIP_H

#define SECONDS_FOR_DYING 3
static const float maxScale = 0.35f;

#include <SFML/Graphics.hpp>
#include "Cannon.h"
#include <memory>

class Spaceship {
public:
    Spaceship(float hp, float strength, float speed, float fireRate, float maxHp);

    virtual ~Spaceship();

    virtual void move(float time) = 0;

    virtual std::unique_ptr<Projectile> useCannon(float dt, Cannon *cannon);

    virtual void receiveDamage(float damage);

    float getHp() const;

    void setHp(float hp);

    float getStrength() const;

    virtual void setStrength(float strength);

    float getSpeed() const;

    void setSpeed(float speed);

    sf::Sprite &getSprite();

    Cannon &getPrimaryCannon();

    const sf::RectangleShape &getBoundingBox() const;

    virtual void blink(float time);

    bool die(float time);

    float getMaxHp() const;

    float getFireRate() const;

    void setFireRate(float fireRate);

    bool isReceivingDamage() const;

    void setReceivingDamage(bool receivingDamage);


protected:
    float hp;
    float strength;
    float speed;
    float fireRate;
    float maxHp;
    sf::Sprite sprite;
    Cannon primaryCannon;
    float elapsedTime = 0;
    float blinkingTime = 0;
    float dyingTime = 0;
    bool receivingDamage = false;
    sf::RectangleShape boundingBox;
};


#endif //ASPACEGAME_SPACESHIP_H
