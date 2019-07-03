//
// Created by Fabio Luccioletti on 2019-07-02.
//

#ifndef ASPACEGAME_MINION_H
#define ASPACEGAME_MINION_H


#include "Enemy.h"
#include "Game.h"

class Minion : public Enemy {
public:
    Minion();

    void move(float time) override;
};

#endif //ASPACEGAME_MINION_H
