//
// Created by Fabio Luccioletti on 2019-07-03.
//

#ifndef ASPACEGAME_RANDOMIZER_H
#define ASPACEGAME_RANDOMIZER_H


#include <SFML/Graphics.hpp>

class Randomizer {

public:
    static sf::Vector2f getRandomPosition(float xMin, float xMax, float yMin, float yMax);

    static float getRandomReal(float min, float max);

    static int getRandomInt(int min, int max);

};


#endif //ASPACEGAME_RANDOMIZER_H
