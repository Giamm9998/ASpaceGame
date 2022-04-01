//
// Created by Fabio Luccioletti on 2019-07-01.
//

#ifndef ASPACEGAME_FIRERATE_H
#define ASPACEGAME_FIRERATE_H


#include "PowerUp.h"

class FireRate : public PowerUp {
public:
    FireRate();

    void powerUp(Player &player) const override;
};


#endif //ASPACEGAME_FIRERATE_H
