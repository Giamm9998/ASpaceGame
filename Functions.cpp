//
// Created by Fabio Luccioletti on 2019-07-03.
//

#include <random>
#include "Functions.h"

sf::Vector2f getRandomPosition(float xMin, float xMax, float yMin, float yMax) {
    std::random_device rd;
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_real_distribution<float> uniX(xMin, xMax);
    std::uniform_real_distribution<float> uniY(yMin, yMax);

    auto randomX = uniX(rng);
    auto randomY = uniY(rng);
    return {randomX, randomY};
}

float getRandomReal(float min, float max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> uni(min, max);

    auto random = uni(rng);
    return random;
}

int getRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);

    auto random = uni(rng);
    return random;
}

EnemyType getRandomEnemy(int minionRatio, int fighterRatio, int assaulterRatio, int kamikazeRatio) {
    int enemy = getRandomInt(1, minionRatio + fighterRatio + assaulterRatio + kamikazeRatio);
    if (enemy <= minionRatio)
        return EnemyType::Minion;
    else if (enemy - minionRatio <= fighterRatio)
        return EnemyType::Fighter;
    else if (enemy - minionRatio - fighterRatio <= assaulterRatio)
        return EnemyType::Assaulter;
    else
        return EnemyType::Kamikaze;
}

PowerUpType
getRandomPowerUp(int commonRatio, int specialRatio, bool hasMaxHp, bool isLaserActive, bool hasThreeCannons) {
    int powerUp = getRandomInt(1, 1);
    if (powerUp <= commonRatio) {
        switch (getRandomInt(1, 1)) {
            case 1:
                return PowerUpType::EnhanceSpecial;
            case 2:
                return PowerUpType::FireRate;
            case 3:
                return PowerUpType::Strength;
            case 4:
                return PowerUpType::FullHealth;
        }
    } else {
        switch (getRandomInt(1, 3 - isLaserActive - hasThreeCannons)) {
            case 1:
                return PowerUpType::EnhanceSpecial;
            case 2:
                if (isLaserActive)
                    return PowerUpType::AuxiliaryCannon;
                else
                    return PowerUpType::LaserCannon;
            case 3:
                return PowerUpType::AuxiliaryCannon;
        }
    }

}
