//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_SPACESHIP_H
#define ASPACEGAME_SPACESHIP_H

static const float dyingDuration = 3;
static const float playerBlinkDuration = 0.3;
static const float maxScale = 0.35;

#include <SFML/Graphics.hpp>
#include "Cannon.h"
#include "Animator.h"
#include <memory>
#include <SFML/Audio/Sound.hpp>

class Spaceship {
public:
    Spaceship(float hp, float strength, float speed, float fireRate, Cannon cannon, int explosionNum);

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

    sf::RectangleShape &getBoundingBox();

    virtual void blink(float time) = 0;

    virtual bool die(float time) = 0;

    float getMaxHp() const;

    float getFireRate() const;

    bool isReceivingDamage() const;

    void setReceivingDamage(bool receiveDamage);

    float getDyingTime() const;

    const std::list<sf::Sprite> &getExplosions() const;

    float getElapsedTime() const;

    void setElapsedTime(float time);

    sf::Sound &getExplosionSound();

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
    int explosionNum;
    std::list<sf::Sprite> explosions;
    std::list<std::unique_ptr<Animator>> animators;
    sf::Sound explosionSound;
};


#endif //ASPACEGAME_SPACESHIP_H
