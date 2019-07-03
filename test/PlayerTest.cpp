//
// Created by Fabio Luccioletti on 2019-07-03.
//

#include "gtest/gtest.h"
#include "../Raptor.h"
#include "../Bomber.h"

TEST(BomberTest, Constructor) {
    Bomber bomber;
    ASSERT_EQ(bomber.getHp(), 150);
    ASSERT_EQ(bomber.getSpeed(), 120);
    ASSERT_EQ(bomber.getStrength(), 10);
    ASSERT_EQ(bomber.getPrimaryCannon().getFireRate(), 200);
    ASSERT_EQ(bomber.getPrimaryCannon().getNShots(), 1);
    ASSERT_EQ(bomber.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(bomber.getPrimaryCannon().getSpaceshipPtr(), &bomber);
    ASSERT_EQ(bomber.getPrimaryCannon().getProjectilePrototype().getSpeed(), 40);
    ASSERT_EQ(bomber.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(bomber.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, -1));
    ASSERT_EQ(bomber.getPrimaryCannon().getProjectilePrototype().getDamage(), bomber.getStrength());
    ASSERT_EQ(bomber.getPrimaryCannon().getProjectilePrototype().getCannonPtr(), &(bomber.getPrimaryCannon()));
    ASSERT_EQ(bomber.getSecondaryCannon().getFireRate(), 100);
    ASSERT_EQ(bomber.getSecondaryCannon().getNShots(), 1);
    ASSERT_EQ(bomber.getSecondaryCannon().isTracker(), false);
    ASSERT_EQ(bomber.getSecondaryCannon().getSpaceshipPtr(), &bomber);
    ASSERT_EQ(bomber.getSecondaryCannon().getProjectilePrototype().getSpeed(), 40);
    ASSERT_EQ(bomber.getSecondaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.9, 0.9));
    ASSERT_EQ(bomber.getSecondaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, -1));
    ASSERT_EQ(bomber.getSecondaryCannon().getProjectilePrototype().getDamage(), bomber.getStrength() * 3);
    ASSERT_EQ(bomber.getSecondaryCannon().getProjectilePrototype().getCannonPtr(), &(bomber.getSecondaryCannon()));
}

TEST(RaptorTest, Constructor) {
    Raptor raptor;
    ASSERT_EQ(raptor.getHp(), 100);
    ASSERT_EQ(raptor.getSpeed(), 150);
    ASSERT_EQ(raptor.getStrength(), 8);
    ASSERT_EQ(raptor.getPrimaryCannon().getFireRate(), 300);
    ASSERT_EQ(raptor.getPrimaryCannon().getNShots(), 1);
    ASSERT_EQ(raptor.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(raptor.getPrimaryCannon().getSpaceshipPtr(), &raptor);
    ASSERT_EQ(raptor.getPrimaryCannon().getProjectilePrototype().getSpeed(), 40);
    ASSERT_EQ(raptor.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(raptor.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, -1));
    ASSERT_EQ(raptor.getPrimaryCannon().getProjectilePrototype().getDamage(), raptor.getStrength());
    ASSERT_EQ(raptor.getPrimaryCannon().getProjectilePrototype().getCannonPtr(), &(raptor.getPrimaryCannon()));
}
