//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_ASSAULTER_H
#define ASPACEGAME_ASSAULTER_H

#include "Enemy.h"

class Assaulter : public Enemy {
public:
    Assaulter();

    void move(float time) override;

    Projectile *useCannon(float dt) override;

    Projectile *useCannon(float dt, sf::Vector2f playerPos);



private:
    bool moved = false;
    const int escapeSpeed = 1;
};


#endif //ASPACEGAME_ASSAULTER_H
