//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_RAPTOR_H
#define ASPACEGAME_RAPTOR_H


#include "Player.h"

class Raptor: public Player{
public:
    Raptor();
    void useSpecialPower() override;

    sf::CircleShape &getShield();

private:
    sf::CircleShape shield;

};


#endif //ASPACEGAME_RAPTOR_H
