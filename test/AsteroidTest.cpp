//
// Created by gianmarco on 10/07/19.
//

#include "gtest/gtest.h"
#include "../Asteroid.h"
#include "../Game.h"

TEST(AsteroidTest, constructor) {
    Asteroid asteroid;
    ASSERT_TRUE(asteroid.getSpeedTest() < asteroidMaxSpeed && asteroid.getSpeedTest() > asteroidMinSpeed);
    ASSERT_TRUE(asteroid.getSize() < asteroidMaxSize && asteroid.getSize() > asteroidMinSize);
    ASSERT_TRUE(asteroid.getSprite().getPosition().x > 0 && asteroid.getSprite().getPosition().x < windowWidth);
}