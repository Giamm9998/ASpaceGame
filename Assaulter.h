//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_ASSAULTER_H
#define ASPACEGAME_ASSAULTER_H

static const int escapeSpeed = 1;

#include "Enemy.h"

class Assaulter : public Enemy {
public:
    Assaulter();

    void move(float time) override;

private:
    float elapsedTime;
    bool moved = false;
};


#endif //ASPACEGAME_ASSAULTER_H
