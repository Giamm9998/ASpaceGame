//
// Created by gianmarco on 15/07/19.
//

#include "Factory.h"
#include "Minion.h"
#include "Kamikaze.h"
#include "Assaulter.h"
#include "Fighter.h"
#include "Boss.h"
#include "Speed.h"
#include "FireRate.h"
#include "Strength.h"
#include "Health.h"
#include "AuxiliaryCannon.h"
#include "LaserCannon.h"
#include "EnhanceSpecial.h"

Factory::~Factory() = default;

Factory::Factory() = default;

std::unique_ptr<Enemy> Factory::createEnemy(EnemyType type) {
    switch (type) {
        case EnemyType::Minion:
            return std::unique_ptr<Enemy>(new Minion);
        case EnemyType::Kamikaze:
            return std::unique_ptr<Enemy>(new Kamikaze);
        case EnemyType::Assaulter:
            return std::unique_ptr<Enemy>(new Assaulter);
        case EnemyType::Fighter:
            return std::unique_ptr<Enemy>(new Fighter);
        case EnemyType::Boss:
            return std::unique_ptr<Enemy>(new Boss);
    }
}

std::unique_ptr<PowerUp> Factory::createPowerUp(PowerUpType type) {
    switch (type) {
        case PowerUpType::Speed:
            return std::unique_ptr<PowerUp>(new Speed);
        case PowerUpType::FireRate:
            return std::unique_ptr<PowerUp>(new FireRate);
        case PowerUpType::Strength:
            return std::unique_ptr<PowerUp>(new Strength);
        case PowerUpType::Health:
            return std::unique_ptr<PowerUp>(new Health);
        case PowerUpType::AuxiliaryCannon:
            return std::unique_ptr<PowerUp>(new AuxiliaryCannon);
        case PowerUpType::LaserCannon:
            return std::unique_ptr<PowerUp>(new LaserCannon);
        case PowerUpType::EnhanceSpecial:
            return std::unique_ptr<PowerUp>(new EnhanceSpecial);
    }
}
