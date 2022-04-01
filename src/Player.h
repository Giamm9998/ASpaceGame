//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_PLAYER_H
#define ASPACEGAME_PLAYER_H

static const int playerSpawnHeight = 80;
static const float laserDPS = 7.5f;

#include "Spaceship.h"
#include "Animator.h"
#include "SFML/Audio.hpp"

class Player :public Spaceship{
public:
    Player(float hp, float strength, float speed, float fireRate, const Cannon &cannon);

    ~Player() override;

    void move(float time) override {};

    virtual void move(float time, short int movement);

    bool isCharging() const;

    void receiveDamage(float damage) final;

    void setStrength(float strength) final;

    std::vector<Cannon> &getAuxiliaryCannons();

    bool isLaserActive() const;

    void setLaserActive(bool active);

    sf::Sprite &getLaser();

    virtual void recharge(float time, sf::RectangleShape &specialHud) = 0;

    void blink(float time) final;

    bool die(float time) override;

    Animator *getLaserAnimator() const;

    sf::Sound &getLaserSound();

    sf::Sound &getPowerUpSound();

    sf::Sound &getHitSound();

    bool isMovable() const;

    void setMovable(bool move);

    void setCharging(bool charge);

protected:
    bool charging;
    bool movable = true;
    std::vector<Cannon> auxiliaryCannons;
    bool laserActive;
    sf::Sprite laser;
    Animator *laserAnimator = new Animator(laser);
    sf::Sound laserSound;
    sf::Sound powerUpSound;
    sf::Sound hitSound;

};


#endif //ASPACEGAME_PLAYER_H
