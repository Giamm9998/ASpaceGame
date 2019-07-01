//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_KAMIKAZE_H
#define ASPACEGAME_KAMIKAZE_H


#include "Enemy.h"

class Kamikaze: public Enemy {
public:
    Kamikaze();
    void move() override;
    void attract();
    void explode();
};


#endif //ASPACEGAME_KAMIKAZE_H
