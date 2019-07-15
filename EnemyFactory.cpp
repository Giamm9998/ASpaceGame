//
// Created by gianmarco on 15/07/19.
//

#include "EnemyFactory.h"
#include "Minion.h"
#include "Kamikaze.h"
#include "Assaulter.h"
#include "Fighter.h"
#include "Boss.h"

EnemyFactory::~EnemyFactory() = default;

EnemyFactory::EnemyFactory() = default;

std::unique_ptr<Enemy> EnemyFactory::createEnemy(EnemyType type) {
    std::unique_ptr<Enemy> result;
    switch (type) {
        case EnemyType::Minion:
            result = std::unique_ptr<Enemy>(new Minion);
            break;
        case EnemyType::Kamikaze:
            result = std::unique_ptr<Enemy>(new Kamikaze);
            break;
        case EnemyType::Assaulter:
            result = std::unique_ptr<Enemy>(new Assaulter);
            break;
        case EnemyType::Fighter:
            result = std::unique_ptr<Enemy>(new Fighter);
            break;
        case EnemyType::Boss:
            result = std::unique_ptr<Enemy>(new Boss);
            break;
    }
    return std::move(result);
}
