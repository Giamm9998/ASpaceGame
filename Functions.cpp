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