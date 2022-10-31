//
// Created by Fabio Luccioletti on 2019-07-01.
//

#ifndef ASPACEGAME_SPEED_H
#define ASPACEGAME_SPEED_H


#include "PowerUp.h"

class Speed : public PowerUp {
public:
    Speed();

    void powerUp(Player &player) const override;
};


#endif //ASPACEGAME_SPEED_H
