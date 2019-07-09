//
// Created by Fabio Luccioletti on 2019-07-01.
//

#ifndef ASPACEGAME_STRENGTH_H
#define ASPACEGAME_STRENGTH_H


#include "PowerUp.h"

class Strength : public PowerUp {
public:
    Strength();

    void powerUp(Player &player) override;
};


#endif //ASPACEGAME_STRENGTH_H
