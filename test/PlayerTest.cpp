//
// Created by Fabio Luccioletti on 2019-07-03.
//

#include "gtest/gtest.h"
#include "../Raptor.h"
#include "../Bomber.h"

TEST(PlayerTest, Instantiation) {
    Bomber bomber;
    ASSERT_EQ(bomber.getHp(), 150);
}
