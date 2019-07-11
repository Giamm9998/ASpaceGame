//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_KAMIKAZE_H
#define ASPACEGAME_KAMIKAZE_H

static const float kamikazeFreezeDuration = 2;
static const float kamikazeMoveDuration = 0.2;
static const float kamikazeMaxSpawnHeight = 120;
static const float kamikazeSpawnWidth = 150;

#include "Enemy.h"

class Kamikaze: public Enemy {
public:
    Kamikaze();

    void move(float time) override;
    void attract();
    void explode();

private:
    sf::Vector2f movement;
};


#endif //ASPACEGAME_KAMIKAZE_H
