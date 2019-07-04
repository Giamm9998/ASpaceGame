//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_BOMBER_H
#define ASPACEGAME_BOMBER_H


#include "Player.h"

class Bomber: public Player {
public:
    Bomber();

    std::unique_ptr<Projectile> useBomb(float dt);

    Cannon &getSecondaryCannon();


private:
    Cannon secondaryCannon;
};


#endif //ASPACEGAME_BOMBER_H
