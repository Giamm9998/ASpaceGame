//
// Created by Fabio Luccioletti on 2019-07-03.
//

#ifndef ASPACEGAME_FUNCTIONS_H
#define ASPACEGAME_FUNCTIONS_H


#include <SFML/Graphics.hpp>
#include "Factory.h"

sf::Vector2f getRandomPosition(float xMin, float xMax, float yMin, float yMax);

float getRandomReal(float min, float max);

int getRandomInt(int min, int max);

EnemyType getRandomEnemy(int minionRatio = 1, int fighterRatio = 1, int assaulterRatio = 1, int kamikazeRatio = 1);

PowerUpType
getRandomPowerUp(int commonRatio = 9, int specialRatio = 1, bool hasMaxHp = 1, bool isLaserActive = false,
                 bool hasThreeCannons = false);

#endif //ASPACEGAME_FUNCTIONS_H
