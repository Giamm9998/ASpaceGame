//
// Created by Fabio Luccioletti on 2019-07-03.
//

#include "gtest/gtest.h"
#include "../Background.h"
#include "../Game.h"

TEST(BackgroundTest, Constructor) {
    Background background;
    ASSERT_EQ(background.getScrollSpeed(), 75);
    ASSERT_EQ(background.getSprite1().getPosition(), sf::Vector2f(0, 0));
    ASSERT_EQ(background.getSprite2().getPosition(), sf::Vector2f(0, -windowHeight));
    ASSERT_FALSE(background.getSprite1().getPosition().y > windowHeight);
}