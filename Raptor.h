//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_RAPTOR_H
#define ASPACEGAME_RAPTOR_H

static const int rechargeTime = 60;

#include "Player.h"

class Raptor: public Player{
public:
    Raptor();

    sf::CircleShape &getShield();

    void move(float time, short int movement) override;

    void useShield(float dt, sf::RectangleShape &specialHud);

    void recharge(float dt, sf::RectangleShape &specialHud) override;

    float getShieldDuration() const;

    void setShieldDuration(float duration);

private:
    sf::CircleShape shield;
    float shieldDuration;

};


#endif //ASPACEGAME_RAPTOR_H
