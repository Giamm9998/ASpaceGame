//
// Created by Fabio Luccioletti on 2019-07-03.
//

#ifndef ASPACEGAME_RANDOMIZER_H
#define ASPACEGAME_RANDOMIZER_H


#include <SFML/Graphics.hpp>

class Randomizer {

public:
    static sf::Vector2f getRandomPosition(int xMin, int xMax, int yMin, int yMax);

};


#endif //ASPACEGAME_RANDOMIZER_H
