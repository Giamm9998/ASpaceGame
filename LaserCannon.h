//
// Created by Fabio Luccioletti on 2019-07-01.
//

#ifndef ASPACEGAME_LASERCANNON_H
#define ASPACEGAME_LASERCANNON_H


#include "PowerUp.h"

class LaserCannon : public PowerUp {
public:
    LaserCannon();

    void powerUp() override;
};


#endif //ASPACEGAME_LASERCANNON_H
