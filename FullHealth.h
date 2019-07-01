//
// Created by Fabio Luccioletti on 2019-07-01.
//

#ifndef ASPACEGAME_FULLHEALTH_H
#define ASPACEGAME_FULLHEALTH_H


#include "PowerUp.h"

class FullHealth : public PowerUp {
public:
    FullHealth();

    void powerUp() override;
};


#endif //ASPACEGAME_FULLHEALTH_H
