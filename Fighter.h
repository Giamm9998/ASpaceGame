//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_FIGHTER_H
#define ASPACEGAME_FIGHTER_H


#include "Enemy.h"

class Fighter: public Enemy{
public:
    Fighter();

    void move(float time) override;

    std::unique_ptr<Projectile> useCannon(float dt, Cannon *cannon) override;

    std::vector<Cannon> &getExternalCannons();

private:
    std::vector<Cannon> externalCannons;
};


#endif //ASPACEGAME_FIGHTER_H
