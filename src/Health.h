//
// Created by Fabio Luccioletti on 2019-07-01.
//

#ifndef ASPACEGAME_HEALTH_H
#define ASPACEGAME_HEALTH_H


#include "PowerUp.h"

class Health : public PowerUp {
public:
    Health();

    void powerUp(Player &player) const override;
};


#endif //ASPACEGAME_HEALTH_H
