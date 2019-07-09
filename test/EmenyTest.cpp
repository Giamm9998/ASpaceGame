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
    ASSERT_EQ(minion.getHp(), 30);
    ASSERT_EQ(minion.getHp(), minion.getMaxHp());
    ASSERT_EQ(minion.getSpeed(), 100);
    ASSERT_EQ(minion.getStrength(), 10);
    ASSERT_EQ(minion.getFireRate(), 0.4f);
    ASSERT_EQ(minion.isReceivingDamage(), false);
    ASSERT_EQ(minion.getPrimaryCannon().getStrengthMultiplier(), 1);
    ASSERT_EQ(minion.getPrimaryCannon().getElapsedtime(), 0);
    ASSERT_EQ(minion.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().isEvil(), true);
    ASSERT_EQ(minion.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(minion.getPrimaryCannon().getSpaceshipPtr(), &minion);
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getSpeed(), 200);
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));
    ASSERT_EQ(minion.getPrimaryCannon().getProjectilePrototype().getDamage(),
              minion.getStrength() * minion.getPrimaryCannon().getStrengthMultiplier());
    ASSERT_EQ(minion.getPrimaryCannon().getRelativePosition(), sf::Vector2f(0, 0));
}

TEST(AssaulterTest, Constructor) {
    Assaulter assaulter;
    ASSERT_EQ(assaulter.getHp(), 60);
    ASSERT_EQ(assaulter.getHp(), assaulter.getMaxHp());
    ASSERT_EQ(assaulter.getSpeed(), 0);
    ASSERT_EQ(assaulter.getStrength(), 20);
    ASSERT_EQ(assaulter.getFireRate(), 0.5f);
    ASSERT_EQ(assaulter.isReceivingDamage(), false);
    ASSERT_EQ(assaulter.getPrimaryCannon().getStrengthMultiplier(), 1);
    ASSERT_EQ(assaulter.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_EQ(assaulter.getPrimaryCannon().getElapsedtime(), 0);
    ASSERT_EQ(assaulter.getPrimaryCannon().getRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().isEvil(), true);
    ASSERT_EQ(assaulter.getPrimaryCannon().isTracker(), true);
    ASSERT_EQ(assaulter.getPrimaryCannon().getSpaceshipPtr(), &assaulter);
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getSpeed(), 100);
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));
    ASSERT_EQ(assaulter.getPrimaryCannon().getProjectilePrototype().getDamage(),
              assaulter.getStrength() * assaulter.getPrimaryCannon().getStrengthMultiplier());
}

TEST(KamikazeTest, Constructor) {
    Kamikaze kamikaze;
    ASSERT_EQ(kamikaze.getHp(), 60);
    ASSERT_EQ(kamikaze.getMaxHp(), kamikaze.getHp());
    ASSERT_EQ(kamikaze.getSpeed(), 70);
    ASSERT_EQ(kamikaze.getStrength(), 30);
    ASSERT_EQ(kamikaze.getFireRate(), 0.8f);
    ASSERT_EQ(kamikaze.isReceivingDamage(), false);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getStrengthMultiplier(), 1);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getElapsedtime(), 0);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_EQ(kamikaze.getPrimaryCannon().getProjectilePrototype().isEvil(), true);
    ASSERT_EQ(kamikaze.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getSpaceshipPtr(), &kamikaze);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getProjectilePrototype().getSpeed(), 200);
    ASSERT_EQ(kamikaze.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(kamikaze.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));
    ASSERT_EQ(kamikaze.getPrimaryCannon().getProjectilePrototype().getDamage(),
              kamikaze.getStrength() * kamikaze.getPrimaryCannon().getStrengthMultiplier());
}

TEST(FighterTest, Constructor) {
    Fighter fighter;
    ASSERT_EQ(fighter.getHp(), 60);
    ASSERT_EQ(fighter.getHp(), fighter.getMaxHp());
    ASSERT_EQ(fighter.getSpeed(), 70);
    ASSERT_EQ(fighter.getStrength(), 10);
    ASSERT_EQ(fighter.isReceivingDamage(), false);
    ASSERT_EQ(fighter.getFireRate(), 0.3f);
    ASSERT_EQ(fighter.getPrimaryCannon().getStrengthMultiplier(), 1);
    ASSERT_EQ(fighter.getPrimaryCannon().getElapsedtime(), 0);
    ASSERT_EQ(fighter.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_EQ(fighter.getPrimaryCannon().getRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().isEvil(), true);
    ASSERT_EQ(fighter.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(fighter.getPrimaryCannon().getSpaceshipPtr(), &fighter);
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getSpeed(), 200);
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, 1));
    ASSERT_EQ(fighter.getPrimaryCannon().getProjectilePrototype().getDamage(),
              fighter.getStrength() * fighter.getPrimaryCannon().getStrengthMultiplier());
    ASSERT_EQ(fighter.getExternalCannons()[0].getRelativePosition(), sf::Vector2f(-114, 0));
    ASSERT_EQ(fighter.getExternalCannons()[1].getRelativePosition(), sf::Vector2f(114, 0));
    ASSERT_EQ(fighter.getExternalCannons().size(), 2);
}