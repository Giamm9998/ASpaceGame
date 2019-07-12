//
// Created by Fabio Luccioletti on 2019-07-03.
//

#ifndef ASPACEGAME_FUNCTIONS_H
#define ASPACEGAME_FUNCTIONS_H


#include <SFML/Graphics.hpp>

sf::Vector2f getRandomPosition(float xMin, float xMax, float yMin, float yMax);

float getRandomReal(float min, float max);

int getRandomInt(int min, int max);

#endif //ASPACEGAME_FUNCTIONS_H
