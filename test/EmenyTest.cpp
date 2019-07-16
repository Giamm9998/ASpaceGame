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
    ASSERT_FLOAT_EQ(minion.getHp(), 75.f);
    ASSERT_FLOAT_EQ(minion.getHp(), minion.getMaxHp());
    ASSERT_FLOAT_EQ(minion.getSpeed(), 100.f);
    ASSERT_FLOAT_EQ(minion.getStrength(), 15.f);
    ASSERT_FLOAT_EQ(minion.getFireRate(), 0.5f);
    ASSERT_FALSE(minion.isReceivingDamage());
    ASSERT_FLOAT_EQ(minion.getPrimaryCannon().getStrengthMultiplier(), 1.f);
    ASSERT_FLOAT_EQ(minion.getPrimaryCannon().getElapsedTime(), 0.f);
    ASSERT_FLOAT_EQ(minion.getPrimaryCannon().getFireRateMultiplier(), 1.f);
    ASSERT_TRUE(minion.getPrimaryCannon().getProjectilePrototype().isEvil());
    ASSERT_FALSE(minion.getPrimaryCannon().isTracker());
    ASSERT_FLOAT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getSpeed(), 250.f);
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));
    ASSERT_FLOAT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getDamage(),
              minion.getStrength() * minion.getPrimaryCannon().getStrengthMultiplier());
    ASSERT_EQ(minion.getPrimaryCannon().getLocalRelativePosition(), sf::Vector2f(0, 0));
}

TEST(AssaulterTest, Constructor) {
    Assaulter assaulter;
    ASSERT_EQ(assaulter.getHp(), 100);
    ASSERT_EQ(assaulter.getHp(), assaulter.getMaxHp());
    ASSERT_EQ(assaulter.getSpeed(), 0);
    ASSERT_EQ(assaulter.getStrength(), 25);
    ASSERT_EQ(assaulter.getFireRate(), 0.5f);
    ASSERT_EQ(assaulter.isReceivingDamage(), false);
    ASSERT_EQ(assaulter.getPrimaryCannon().getStrengthMultiplier(), 1);
    ASSERT_EQ(assaulter.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_EQ(assaulter.getPrimaryCannon().getElapsedTime(), 0);
    ASSERT_EQ(assaulter.getPrimaryCannon().getLocalRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().isEvil(), true);
    ASSERT_EQ(assaulter.getPrimaryCannon().isTracker(), true);
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getSpeed(), 300);
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getDamage(),
              assaulter.getStrength() * assaulter.getPrimaryCannon().getStrengthMultiplier());
}

TEST(KamikazeTest, Constructor) {
    Kamikaze kamikaze;
    ASSERT_FLOAT_EQ(kamikaze.getHp(), 150.f);
    ASSERT_FLOAT_EQ(kamikaze.getMaxHp(), kamikaze.getHp());
    ASSERT_FLOAT_EQ(kamikaze.getSpeed(), 70.f);
    ASSERT_FLOAT_EQ(kamikaze.getStrength(), 30.f);
    ASSERT_FLOAT_EQ(kamikaze.getFireRate(), 0.8f);
    ASSERT_FALSE(kamikaze.isReceivingDamage());
}

TEST(FighterTest, Constructor) {
    Fighter fighter;
    ASSERT_EQ(fighter.getHp(), 125);
    ASSERT_EQ(fighter.getHp(), fighter.getMaxHp());
    ASSERT_EQ(fighter.getSpeed(), 70);
    ASSERT_EQ(fighter.getStrength(), 20);
    ASSERT_EQ(fighter.isReceivingDamage(), false);
    ASSERT_EQ(fighter.getFireRate(), 0.6f);
    ASSERT_EQ(fighter.getPrimaryCannon().getStrengthMultiplier(), 1);
    ASSERT_EQ(fighter.getPrimaryCannon().getElapsedTime(), 0);
    ASSERT_EQ(fighter.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_EQ(fighter.getPrimaryCannon().getLocalRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().isEvil(), true);
    ASSERT_EQ(fighter.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getSpeed(), 250);
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getDamage(),
              fighter.getStrength() * fighter.getPrimaryCannon().getStrengthMultiplier());
    ASSERT_EQ(fighter.getExternalCannons()[0].getLocalRelativePosition(), sf::Vector2f(-114, 0));
    ASSERT_EQ(fighter.getExternalCannons()[1].getLocalRelativePosition(), sf::Vector2f(114, 0));
    ASSERT_EQ(fighter.getExternalCannons().size(), 2);
}

TEST(EnemyTest, Die) {
    Minion minion;
    bool a = minion.die(dyingDuration - 1);
    ASSERT_FALSE(a);
    a = minion.die(2);
    ASSERT_TRUE(a);
}