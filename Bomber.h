//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_BOMBER_H
#define ASPACEGAME_BOMBER_H


#include "Player.h"

class Bomber: public Player {
public:
    Bomber();

    void useSpecialPower() override;

private:
    Cannon secondaryCannon;
};


#endif //ASPACEGAME_BOMBER_H
