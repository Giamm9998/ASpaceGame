//
// Created by gianmarco on 15/07/19.
//

#ifndef ASPACEGAME_ENEMYFACTORY_H
#define ASPACEGAME_ENEMYFACTORY_H

#include <memory>
#include "Enemy.h"

enum class EnemyType {
    Kamikaze, Assaulter, Fighter, Minion, Boss
};

class EnemyFactory {
public:

    EnemyFactory();

    virtual ~EnemyFactory();

    static std::unique_ptr<Enemy> createEnemy(EnemyType type);
};


#endif //ASPACEGAME_ENEMYFACTORY_H
