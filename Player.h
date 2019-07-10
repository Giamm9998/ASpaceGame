//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_PLAYER_H
#define ASPACEGAME_PLAYER_H

static const int PlayerSpawnHeight = 80;
static const float laserDPS = 20.f;

#include "Spaceship.h"

class Player :public Spaceship{
public:
    Player(float hp, float strength, float speed, float fireRate);

    void move(float time) override {};

    virtual void move(float time, short int movement);

    bool isCharging() const;

    void receiveDamage(float damage) final;

    void setStrength(float strength) final;

    std::vector<Cannon> &getAuxiliaryCannons();

    bool isLaserActive() const;

    void setLaserActive(bool active);

    sf::RectangleShape &getLaser();

    virtual void recharge(float time, sf::RectangleShape &specialHud) = 0;

protected:
    bool charging;
    std::vector<Cannon> auxiliaryCannons;
    bool laserActive;
    sf::RectangleShape laser;

};


#endif //ASPACEGAME_PLAYER_H
