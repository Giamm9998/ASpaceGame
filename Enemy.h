//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_ENEMY_H
#define ASPACEGAME_ENEMY_H


static const float enemyBlinkDuration = 0.15;

#include "Spaceship.h"
#include <list>
#include "Game.h"
#include "Animator.h"

class Enemy: public Spaceship{

public:
    Enemy(float hp, float strength, float speed, float fireRate, const Cannon &cannon);

    ~Enemy() override;

    void setPosition(float x, float y);

    void setPosition(const sf::Vector2f &pos);

    void move(float time) override; //Todo make abstract

    void blink(float time) final;

    bool die(float time) override;

    const std::list<sf::Sprite> &getExplosions() const;

protected:
    short int direction = right;
    std::list<sf::Sprite> explosions;
    std::list<Animator *> animators;
};


#endif //ASPACEGAME_ENEMY_H
