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
    ASSERT_FALSE(assaulter.isMovedTest());
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

TEST(BossTest, constructor) {
    Boss boss;

    //ASSERT_TRUE(EntityManager::isOutOfSight(boss.getSprite()));
    ASSERT_FLOAT_EQ(boss.getElapsedTime(), -6.7);
    ASSERT_FLOAT_EQ(boss.getHp(), 1000);
    ASSERT_FLOAT_EQ(boss.getHp(), boss.getMaxHp());
    ASSERT_FLOAT_EQ(boss.getStrength(), 15);
    ASSERT_FLOAT_EQ(boss.getSpeed(), 50);
    ASSERT_FLOAT_EQ(boss.getFireRate(), 1);
    ASSERT_DOUBLE_EQ(boss.getAngle(), M_PI / 4);
    ASSERT_FLOAT_EQ(boss.getMobileTime(), 0);
    ASSERT_FLOAT_EQ(boss.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_FLOAT_EQ(boss.getPrimaryCannon().getStrengthMultiplier(), 1);
    ASSERT_EQ(boss.getPrimaryCannon().getLocalRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_FALSE(boss.isReceivingDamage());
    ASSERT_FALSE(boss.getPrimaryCannon().isTracker());
    ASSERT_FLOAT_EQ(boss.getPrimaryCannon().getProjectilePrototype().getSpeed(), 400);
    ASSERT_FLOAT_EQ(boss.getPrimaryCannon().getProjectilePrototype().getDamage(), 15);
    ASSERT_EQ(boss.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_TRUE(boss.getPrimaryCannon().getProjectilePrototype().isEvil());

    ASSERT_EQ(boss.getSimpleCannons().size(), 2);
    ASSERT_FLOAT_EQ(boss.getSimpleCannons().back().getFireRateMultiplier(), 1);
    ASSERT_FLOAT_EQ(boss.getSimpleCannons().back().getStrengthMultiplier(), 1);
    ASSERT_EQ(boss.getSimpleCannons().back().getLocalRelativePosition(), sf::Vector2f(250, 0));
    ASSERT_EQ(boss.getSimpleCannons().front().getLocalRelativePosition(), sf::Vector2f(-250, 0));
    ASSERT_FALSE(boss.getSimpleCannons().back().isTracker());
    ASSERT_FLOAT_EQ(boss.getSimpleCannons().back().getProjectilePrototype().getSpeed(), 400);
    ASSERT_FLOAT_EQ(boss.getSimpleCannons().back().getProjectilePrototype().getDamage(), 15);
    ASSERT_EQ(boss.getSimpleCannons().back().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_TRUE(boss.getSimpleCannons().back().getProjectilePrototype().isEvil());
    ASSERT_EQ(boss.getSimpleCannons().back().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));

    ASSERT_FLOAT_EQ(boss.getMobileCannon().getFireRateMultiplier(), 1.8);
    ASSERT_FLOAT_EQ(boss.getMobileCannon().getStrengthMultiplier(), 1);
    ASSERT_FALSE(boss.getMobileCannon().isTracker());
    ASSERT_EQ(boss.getMobileCannon().getLocalRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_FLOAT_EQ(boss.getMobileCannon().getElapsedTime(), 0);
    ASSERT_FLOAT_EQ(boss.getMobileCannon().getProjectilePrototype().getSpeed(), 300);
    ASSERT_FLOAT_EQ(boss.getMobileCannon().getProjectilePrototype().getDamage(), 15);
    ASSERT_EQ(boss.getMobileCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_TRUE(boss.getMobileCannon().getProjectilePrototype().isEvil());
    ASSERT_EQ(boss.getMobileCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));

    ASSERT_EQ(boss.getBombCannons().size(), 2);
    ASSERT_FLOAT_EQ(boss.getBombCannons().back().getFireRateMultiplier(), 1);
    ASSERT_FLOAT_EQ(boss.getBombCannons().back().getStrengthMultiplier(), 3);
    ASSERT_EQ(boss.getBombCannons().back().getLocalRelativePosition(), sf::Vector2f(250, 0));
    ASSERT_EQ(boss.getBombCannons().front().getLocalRelativePosition(), sf::Vector2f(-250, 0));
    ASSERT_FALSE(boss.getBombCannons().back().isTracker());
    ASSERT_FLOAT_EQ(boss.getBombCannons().back().getProjectilePrototype().getSpeed(), 400);
    ASSERT_FLOAT_EQ(boss.getBombCannons().back().getProjectilePrototype().getDamage(), 45);
    ASSERT_EQ(boss.getBombCannons().back().getProjectilePrototype().getSize(), sf::Vector2f(0.9, 0.9));
    ASSERT_TRUE(boss.getBombCannons().back().getProjectilePrototype().isEvil());
    ASSERT_EQ(boss.getBombCannons().back().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));

    ASSERT_FLOAT_EQ(boss.getTrackerCannon().getFireRateMultiplier(), 1);
    ASSERT_FLOAT_EQ(boss.getTrackerCannon().getStrengthMultiplier(), 1.5);
    ASSERT_TRUE(boss.getTrackerCannon().isTracker());
    ASSERT_EQ(boss.getTrackerCannon().getLocalRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_FLOAT_EQ(boss.getTrackerCannon().getProjectilePrototype().getSpeed(), 300);
    ASSERT_FLOAT_EQ(boss.getTrackerCannon().getProjectilePrototype().getDamage(), 22.5);
    ASSERT_EQ(boss.getTrackerCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_TRUE(boss.getTrackerCannon().getProjectilePrototype().isEvil());
    ASSERT_EQ(boss.getTrackerCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));

}