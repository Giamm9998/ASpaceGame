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

    float getMaxHp() const;

    bool isCharging() const;

    void receiveDamage(float damage) override;

    void setStrength(float strength) override;

    std::vector<Cannon> &getAuxiliaryCannons();

protected:
    float maxHp;
    bool charging;
    std::vector<Cannon> auxiliaryCannons;

};


#endif //ASPACEGAME_PLAYER_H
