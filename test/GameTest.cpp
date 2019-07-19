//
// Created by Fabio Luccioletti on 2019-06-26.
//

#include "gtest/gtest.h"
#include "../Game.h"

TEST(Game, Constructor) {
    Game game;
    ASSERT_FALSE(game.isUsingSpecialTest());
    ASSERT_FALSE(game.isShootingTest());
    ASSERT_FALSE(game.isMovingRightTest());
    ASSERT_FALSE(game.isMovingLeftTest());
    ASSERT_FALSE(game.isPausedTest());
    ASSERT_EQ(game.getWindowTest().getSize().x, windowWidth);
    ASSERT_EQ(game.getWindowTest().getSize().y, windowHeight);
    ASSERT_TRUE(game.isChoosingPlayerTest());
    ASSERT_FALSE(game.isNameEnteredTest());
}
