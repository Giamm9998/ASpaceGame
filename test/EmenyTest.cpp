//
// Created by Fabio Luccioletti on 2019-07-03.
//

#include "gtest/gtest.h"
#include "../Minion.h"
#include "../Assaulter.h"
#include "../Kamikaze.h"
#include "../Fighter.h"

TEST(MinionTest, Constructor) {
    Minion minion;
    ASSERT_EQ(minion.getHp(), 50);
    ASSERT_EQ(minion.getSpeed(), 100);
    ASSERT_EQ(minion.getStrength(), 10);
    ASSERT_EQ(minion.getPrimaryCannon().getFireRate(), 250);
    ASSERT_EQ(minion.getPrimaryCannon().getNShots(), 1);
    ASSERT_EQ(minion.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(minion.getPrimaryCannon().getSpaceshipPtr(), &minion);
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getSpeed(), 40);
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getDamage(), minion.getStrength());
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getCannonPtr(), &(minion.getPrimaryCannon()));
}

TEST(AssaulterTest, Constructor) {
    Assaulter assaulter;
    ASSERT_EQ(assaulter.getHp(), 50);
    ASSERT_EQ(assaulter.getSpeed(), 30);
    ASSERT_EQ(assaulter.getStrength(), 20);
    ASSERT_EQ(assaulter.getPrimaryCannon().getFireRate(), 100);
    ASSERT_EQ(assaulter.getPrimaryCannon().getNShots(), 1);
    ASSERT_EQ(assaulter.getPrimaryCannon().isTracker(), true);
    ASSERT_EQ(assaulter.getPrimaryCannon().getSpaceshipPtr(), &assaulter);
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getSpeed(), 40);
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getDamage(), assaulter.getStrength());
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getCannonPtr(), &(assaulter.getPrimaryCannon()));
}

TEST(KamikazeTest, Constructor) {
    Kamikaze kamikaze;
    ASSERT_EQ(kamikaze.getHp(), 50);
    ASSERT_EQ(kamikaze.getSpeed(), 30);
    ASSERT_EQ(kamikaze.getStrength(), 30);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getFireRate(), 50);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getNShots(), 1);
    ASSERT_EQ(kamikaze.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getSpaceshipPtr(), &kamikaze);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getProjectilePrototype().getSpeed(), 80);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(kamikaze.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));
    ASSERT_EQ(kamikaze.getPrimaryCannon().getProjectilePrototype().getDamage(), kamikaze.getStrength());
    ASSERT_EQ(kamikaze.getPrimaryCannon().getProjectilePrototype().getCannonPtr(), &(kamikaze.getPrimaryCannon()));
}

TEST(FighterTest, Constructor) {
    Fighter fighter;
    ASSERT_EQ(fighter.getHp(), 50);
    ASSERT_EQ(fighter.getSpeed(), 30);
    ASSERT_EQ(fighter.getStrength(), 10);
    ASSERT_EQ(fighter.getPrimaryCannon().getFireRate(), 250);
    ASSERT_EQ(fighter.getPrimaryCannon().getNShots(), 3);
    ASSERT_EQ(fighter.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(fighter.getPrimaryCannon().getSpaceshipPtr(), &fighter);
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getSpeed(), 40);
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getDamage(), fighter.getStrength());
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getCannonPtr(), &(fighter.getPrimaryCannon()));
}