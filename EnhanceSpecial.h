//
// Created by Fabio Luccioletti on 2019-07-01.
//

#ifndef ASPACEGAME_ENHANCESPECIAL_H
#define ASPACEGAME_ENHANCESPECIAL_H


#include "PowerUp.h"

class EnhanceSpecial : public PowerUp {
public:
    EnhanceSpecial();

    void powerUp(Player *player) override;
};


#endif //ASPACEGAME_ENHANCESPECIAL_H
