//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_SPACESHIP_H
#define ASPACEGAME_SPACESHIP_H

static const float dyingDuration = 3;
static const float playerBlinkDuration = 0.3;
static const float maxScale = 0.35f;

#include <SFML/Graphics.hpp>
#include "Cannon.h"
#include <memory>

class Spaceship {
public:
    Spaceship(float hp, float strength, float speed, float fireRate);

    virtual ~Spaceship();

    virtual void move(float time) = 0;

    virtual std::unique_ptr<Projectile> useCannon(float dt, Cannon &cannon);

    virtual void receiveDamage(float damage);

    float getHp() const;

    void setHp(float newHp);

    float getStrength() const;

    virtual void setStrength(float newStrength);

    float getSpeed() const;

    void setSpeed(float newSpeed);

    sf::Sprite &getSprite();

    Cannon &getPrimaryCannon();

    const sf::RectangleShape &getBoundingBox() const;

    virtual void blink(float time);

    bool die(float time);

    float getMaxHp() const;

    float getFireRate() const;

    void setFireRate(float rate);

    bool isReceivingDamage() const;

    void setReceivingDamage(bool receiveDamage);


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
