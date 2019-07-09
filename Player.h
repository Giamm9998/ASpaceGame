//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_PLAYER_H
#define ASPACEGAME_PLAYER_H

#include "Spaceship.h"

class Player :public Spaceship{
public:
    Player(float hp, float strength, float speed, float fireRate, float maxHp);

    void move(float time) override {};

    virtual void move(float time, short int movement);

    bool isCharging() const;

    void receiveDamage(float damage) override;

    void setStrength(float strength) override;

    std::vector<Cannon> &getAuxiliaryCannons();

    bool isLaserActive() const;

    void setLaserActive(bool laserActive);

    sf::RectangleShape &getLaser();

    virtual void recharge(float time, sf::RectangleShape &specialHud) = 0;

protected:
    bool charging;
    std::vector<Cannon> auxiliaryCannons;
    bool laserActive;
    sf::RectangleShape laser;

};


#endif //ASPACEGAME_PLAYER_H
