//
// Created by Fabio Luccioletti on 2019-07-03.
//

#include <random>
#include "Randomizer.h"

sf::Vector2f Randomizer::getRandomPosition(int xMin, int xMax, int yMin, int yMax) {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_real_distribution<float> uniX(xMin, xMax);
    std::uniform_real_distribution<float> uniY(yMin, yMax);

    auto randomX = uniX(rng);
    auto randomY = uniY(rng);
    return {randomX, randomY};
}