//
// Created by Fabio Luccioletti on 2019-07-03.
//

#include "gtest/gtest.h"
#include "../Minion.h"
#include "../Assaulter.h"
#include "../Kamikaze.h"
#include "../Fighter.h"
#include "../Boss.h"

TEST(MinionTest, Constructor) {
    Minion minion;
    ASSERT_FLOAT_EQ(minion.getHp(), 75.f);
    ASSERT_FLOAT_EQ(minion.getHp(), minion.getMaxHp());
    ASSERT_FLOAT_EQ(minion.getSpeed(), 100.f);
    ASSERT_FLOAT_EQ(minion.getStrength(), 15.f);
    ASSERT_FLOAT_EQ(minion.getFireRate(), 0.5f);
    ASSERT_FALSE(minion.isReceivingDamage());
    ASSERT_FLOAT_EQ(minion.getPrimaryCannon().getStrengthMultiplier(), 1.f);
    ASSERT_FLOAT_EQ(minion.getPrimaryCannon().getElapsedTimeTest(), 0.f);
    ASSERT_FLOAT_EQ(minion.getPrimaryCannon().getFireRateMultiplier(), 1.f);
    ASSERT_TRUE(minion.getPrimaryCannon().getProjectilePrototype().isEvil());
    ASSERT_FALSE(minion.getPrimaryCannon().isTracker());
    ASSERT_FLOAT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getSpeedTest(), 250.f);
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getMovementTest(), sf::Vector2f(0, 1));
    ASSERT_FLOAT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getDamage(),
              minion.getStrength() * minion.getPrimaryCannon().getStrengthMultiplier());
    ASSERT_EQ(minion.getPrimaryCannon().getLocalRelativePosition(), sf::Vector2f(0, 0));
}

TEST(AssaulterTest, Constructor) {
    Assaulter assaulter;
    ASSERT_FALSE(assaulter.isMovedTest());
    ASSERT_EQ(assaulter.getHp(), 100);
    ASSERT_EQ(assaulter.getHp(), assaulter.getMaxHp());
    ASSERT_EQ(assaulter.getSpeed(), 0);
    ASSERT_EQ(assaulter.getStrength(), 25);
    ASSERT_EQ(assaulter.getFireRate(), 0.5f);
    ASSERT_EQ(assaulter.isReceivingDamage(), false);
    ASSERT_EQ(assaulter.getPrimaryCannon().getStrengthMultiplier(), 1);
    ASSERT_EQ(assaulter.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_EQ(assaulter.getPrimaryCannon().getElapsedTimeTest(), 0);
    ASSERT_EQ(assaulter.getPrimaryCannon().getLocalRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().isEvil(), true);
    ASSERT_EQ(assaulter.getPrimaryCannon().isTracker(), true);
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getSpeedTest(), 300);
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getMovementTest(), sf::Vector2f(0, 1));
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getDamage(),
              assaulter.getStrength() * assaulter.getPrimaryCannon().getStrengthMultiplier());
}

TEST(KamikazeTest, Constructor) {
    Kamikaze kamikaze;
    ASSERT_FALSE(kamikaze.isAttacking());
    ASSERT_FALSE(kamikaze.isTargetAcquiredTest());
    ASSERT_FALSE(kamikaze.isTargetAttractedTest());
    ASSERT_FLOAT_EQ(kamikaze.getAcquiringTimeTest(), 0);
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
    ASSERT_EQ(fighter.getPrimaryCannon().getElapsedTimeTest(), 0);
    ASSERT_EQ(fighter.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_EQ(fighter.getPrimaryCannon().getLocalRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().isEvil(), true);
    ASSERT_EQ(fighter.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getSpeedTest(), 250);
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getMovementTest(), sf::Vector2f(0, 1));
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

TEST(BossTest, constructor) {
    Boss boss;
    ASSERT_FLOAT_EQ(boss.getElapsedTime(), -6.7);
    ASSERT_FLOAT_EQ(boss.getHp(), 1000);
    ASSERT_FLOAT_EQ(boss.getHp(), boss.getMaxHp());
    ASSERT_FLOAT_EQ(boss.getStrength(), 15);
    ASSERT_FLOAT_EQ(boss.getSpeed(), 50);
    ASSERT_FLOAT_EQ(boss.getFireRate(), 1);
    ASSERT_DOUBLE_EQ(boss.getAngleTest(), M_PI / 4);
    ASSERT_FLOAT_EQ(boss.getMobileTimeTest(), 0);
    ASSERT_FLOAT_EQ(boss.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_FLOAT_EQ(boss.getPrimaryCannon().getStrengthMultiplier(), 1);
    ASSERT_EQ(boss.getPrimaryCannon().getLocalRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_FALSE(boss.isReceivingDamage());
    ASSERT_FALSE(boss.getPrimaryCannon().isTracker());
    ASSERT_FLOAT_EQ(boss.getPrimaryCannon().getProjectilePrototype().getSpeedTest(), 400);
    ASSERT_FLOAT_EQ(boss.getPrimaryCannon().getProjectilePrototype().getDamage(), 15);
    ASSERT_EQ(boss.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_TRUE(boss.getPrimaryCannon().getProjectilePrototype().isEvil());

    ASSERT_EQ(boss.getSimpleCannonsTest().size(), 2);
    ASSERT_FLOAT_EQ(boss.getSimpleCannonsTest().back().getFireRateMultiplier(), 1);
    ASSERT_FLOAT_EQ(boss.getSimpleCannonsTest().back().getStrengthMultiplier(), 1);
    ASSERT_EQ(boss.getSimpleCannonsTest().back().getLocalRelativePosition(), sf::Vector2f(250, 0));
    ASSERT_EQ(boss.getSimpleCannonsTest().front().getLocalRelativePosition(), sf::Vector2f(-250, 0));
    ASSERT_FALSE(boss.getSimpleCannonsTest().back().isTracker());
    ASSERT_FLOAT_EQ(boss.getSimpleCannonsTest().back().getProjectilePrototype().getSpeedTest(), 400);
    ASSERT_FLOAT_EQ(boss.getSimpleCannonsTest().back().getProjectilePrototype().getDamage(), 15);
    ASSERT_EQ(boss.getSimpleCannonsTest().back().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_TRUE(boss.getSimpleCannonsTest().back().getProjectilePrototype().isEvil());
    ASSERT_EQ(boss.getSimpleCannonsTest().back().getProjectilePrototype().getMovementTest(), sf::Vector2f(0, 1));

    ASSERT_FLOAT_EQ(boss.getMobileCannonTest().getFireRateMultiplier(), 1.8);
    ASSERT_FLOAT_EQ(boss.getMobileCannonTest().getStrengthMultiplier(), 1);
    ASSERT_FALSE(boss.getMobileCannonTest().isTracker());
    ASSERT_EQ(boss.getMobileCannonTest().getLocalRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_FLOAT_EQ(boss.getMobileCannonTest().getElapsedTimeTest(), 0);
    ASSERT_FLOAT_EQ(boss.getMobileCannonTest().getProjectilePrototype().getSpeedTest(), 300);
    ASSERT_FLOAT_EQ(boss.getMobileCannonTest().getProjectilePrototype().getDamage(), 15);
    ASSERT_EQ(boss.getMobileCannonTest().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_TRUE(boss.getMobileCannonTest().getProjectilePrototype().isEvil());
    ASSERT_EQ(boss.getMobileCannonTest().getProjectilePrototype().getMovementTest(), sf::Vector2f(0, 1));

    ASSERT_EQ(boss.getBombCannonsTest().size(), 2);
    ASSERT_FLOAT_EQ(boss.getBombCannonsTest().back().getFireRateMultiplier(), 1);
    ASSERT_FLOAT_EQ(boss.getBombCannonsTest().back().getStrengthMultiplier(), 3);
    ASSERT_EQ(boss.getBombCannonsTest().back().getLocalRelativePosition(), sf::Vector2f(250, 0));
    ASSERT_EQ(boss.getBombCannonsTest().front().getLocalRelativePosition(), sf::Vector2f(-250, 0));
    ASSERT_FALSE(boss.getBombCannonsTest().back().isTracker());
    ASSERT_FLOAT_EQ(boss.getBombCannonsTest().back().getProjectilePrototype().getSpeedTest(), 400);
    ASSERT_FLOAT_EQ(boss.getBombCannonsTest().back().getProjectilePrototype().getDamage(), 45);
    ASSERT_EQ(boss.getBombCannonsTest().back().getProjectilePrototype().getSize(), sf::Vector2f(0.9, 0.9));
    ASSERT_TRUE(boss.getBombCannonsTest().back().getProjectilePrototype().isEvil());
    ASSERT_EQ(boss.getBombCannonsTest().back().getProjectilePrototype().getMovementTest(), sf::Vector2f(0, 1));

    ASSERT_FLOAT_EQ(boss.getTrackerCannonTest().getFireRateMultiplier(), 1);
    ASSERT_FLOAT_EQ(boss.getTrackerCannonTest().getStrengthMultiplier(), 1.5);
    ASSERT_TRUE(boss.getTrackerCannonTest().isTracker());
    ASSERT_EQ(boss.getTrackerCannonTest().getLocalRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_FLOAT_EQ(boss.getTrackerCannonTest().getProjectilePrototype().getSpeedTest(), 300);
    ASSERT_FLOAT_EQ(boss.getTrackerCannonTest().getProjectilePrototype().getDamage(), 22.5);
    ASSERT_EQ(boss.getTrackerCannonTest().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_TRUE(boss.getTrackerCannonTest().getProjectilePrototype().isEvil());
    ASSERT_EQ(boss.getTrackerCannonTest().getProjectilePrototype().getMovementTest(), sf::Vector2f(0, 1));

}