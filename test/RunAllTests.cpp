//
// Created by Fabio Luccioletti on 2019-06-26.
//
#include "gtest/gtest.h"
#include "../ResourceManager.h"
#include "../Game.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    ResourceManager resourceManager;
    return RUN_ALL_TESTS();
}
