//
// Created by gianmarco on 15/07/19.
//

#ifndef ASPACEGAME_FACTORY_H
#define ASPACEGAME_FACTORY_H

#include <memory>
#include "Enemy.h"

enum class EnemyType {
    Kamikaze, Assaulter, Fighter, Minion, Boss
};

enum class PowerUpType {
    Speed, FireRate, Strength, Health, AuxiliaryCannon, LaserCannon, EnhanceSpecial
};

class Factory {
public:

    Factory();

    virtual ~Factory();

    static std::unique_ptr<Enemy> createEnemy(EnemyType type);

    static std::unique_ptr<PowerUp> createPowerUp(PowerUpType type);

};


#endif //ASPACEGAME_FACTORY_H
