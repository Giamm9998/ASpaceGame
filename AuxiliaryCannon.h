//
// Created by Fabio Luccioletti on 2019-07-01.
//

#ifndef ASPACEGAME_AUXILIARYCANNON_H
#define ASPACEGAME_AUXILIARYCANNON_H


#include "PowerUp.h"

class AuxiliaryCannon : public PowerUp {
public:
    AuxiliaryCannon();

    void powerUp(Player &player) override;
};


#endif //ASPACEGAME_AUXILIARYCANNON_H
