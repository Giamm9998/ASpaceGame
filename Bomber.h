//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_BOMBER_H
#define ASPACEGAME_BOMBER_H


static const float bomberStrength = 15;
static const float bomberSecondaryStrengthMult = 3;

#include "Player.h"

class Bomber: public Player {
public:
    Bomber();

    std::unique_ptr<Projectile> useBomb(sf::RectangleShape &specialHud);

    Cannon &getSecondaryCannon();

    void recharge(float dt, sf::RectangleShape &specialHud) override;


private:
    Cannon secondaryCannon;
};


#endif //ASPACEGAME_BOMBER_H
