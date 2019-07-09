//
// Created by Fabio Luccioletti on 2019-07-03.
//

#include "gtest/gtest.h"
#include "../Raptor.h"
#include "../Bomber.h"

TEST(BomberTest, Constructor) {
    Bomber bomber;
    ASSERT_EQ(bomber.getHp(), 200);
    ASSERT_EQ(bomber.getMaxHp(), bomber.getHp());
    ASSERT_EQ(bomber.getSpeed(), 120);
    ASSERT_EQ(bomber.getStrength(), 15);
    ASSERT_EQ(bomber.getFireRate(), 1.2f);
    ASSERT_EQ(bomber.isReceivingDamage(), false);
    ASSERT_EQ(bomber.isCharging(), false);
    ASSERT_EQ(bomber.isLaserActive(), false);
    ASSERT_EQ(bomber.getAuxiliaryCannons().empty(), true);
    ASSERT_EQ(bomber.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(bomber.getPrimaryCannon().getSpaceshipPtr(), &bomber);
    ASSERT_EQ(bomber.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_EQ(bomber.getPrimaryCannon().getStrengthMultiplier(), 1);
    ASSERT_EQ(bomber.getPrimaryCannon().getProjectilePrototype().getSpeed(), 400);
    ASSERT_EQ(bomber.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(bomber.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, -1));
    ASSERT_EQ(bomber.getPrimaryCannon().getProjectilePrototype().getDamage(),
              bomber.getStrength() * bomber.getPrimaryCannon().getStrengthMultiplier());
    ASSERT_EQ(bomber.getPrimaryCannon().getProjectilePrototype().isEvil(), false);
    ASSERT_FLOAT_EQ(bomber.getPrimaryCannon().getElapsedtime(),
                    (1.f / (bomber.getFireRate() * bomber.getPrimaryCannon().getFireRateMultiplier())));
    ASSERT_EQ(bomber.getPrimaryCannon().getRelativePosition(), sf::Vector2f(0, 0));
    ASSERT_EQ(bomber.getSecondaryCannon().isTracker(), false);
    ASSERT_EQ(bomber.getSecondaryCannon().getSpaceshipPtr(), &bomber);
    ASSERT_EQ(bomber.getSecondaryCannon().getFireRateMultiplier(), 0.5);
    ASSERT_EQ(bomber.getSecondaryCannon().getStrengthMultiplier(), 3);
    ASSERT_EQ(bomber.getSecondaryCannon().getProjectilePrototype().isEvil(), false);
    ASSERT_EQ(bomber.getSecondaryCannon().getProjectilePrototype().getSpeed(), 200);
    ASSERT_EQ(bomber.getSecondaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.9, 0.9));
    ASSERT_EQ(bomber.getSecondaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, -1));
    ASSERT_EQ(bomber.getSecondaryCannon().getProjectilePrototype().getDamage(),
              bomber.getStrength() * bomber.getSecondaryCannon().getStrengthMultiplier());
    ASSERT_EQ(bomber.getSecondaryCannon().getElapsedtime(), 0);
    ASSERT_EQ(bomber.getSecondaryCannon().getRelativePosition(), sf::Vector2f(0, 0));
}

TEST(RaptorTest, Constructor) {
    Raptor raptor;
    ASSERT_EQ(raptor.getHp(), 140);
    ASSERT_EQ(raptor.getHp(), raptor.getMaxHp());
    ASSERT_EQ(raptor.getSpeed(), 160);
    ASSERT_EQ(raptor.getStrength(), 10);
    ASSERT_EQ(raptor.getFireRate(), 1.8f);
    ASSERT_EQ(raptor.isReceivingDamage(), false);
    ASSERT_EQ(raptor.isCharging(), false);
    ASSERT_EQ(raptor.isLaserActive(), false);
    ASSERT_EQ(raptor.getShieldDuration(), 5);
    ASSERT_EQ(raptor.getAuxiliaryCannons().empty(), true);
    ASSERT_EQ(raptor.getPrimaryCannon().isTracker(), false);
    ASSERT_EQ(raptor.getPrimaryCannon().getSpaceshipPtr(), &raptor);
    ASSERT_EQ(raptor.getPrimaryCannon().getFireRateMultiplier(), 1);
    ASSERT_EQ(raptor.getPrimaryCannon().getStrengthMultiplier(), 1);
    ASSERT_FLOAT_EQ(raptor.getPrimaryCannon().getElapsedtime(),
                    (1.f / (raptor.getFireRate() * raptor.getPrimaryCannon().getFireRateMultiplier())));
    ASSERT_EQ(raptor.getPrimaryCannon().getProjectilePrototype().isEvil(), false);
    ASSERT_EQ(raptor.getPrimaryCannon().getProjectilePrototype().getSpeed(), 400);
    ASSERT_EQ(raptor.getPrimaryCannon().getProjectilePrototype().getSize(), sf::Vector2f(0.5, 0.5));
    ASSERT_EQ(raptor.getPrimaryCannon().getProjectilePrototype().getMovement(), sf::Vector2f(0, -1));
    ASSERT_EQ(raptor.getPrimaryCannon().getProjectilePrototype().getDamage(),
              raptor.getStrength() * raptor.getPrimaryCannon().getStrengthMultiplier());
    ASSERT_EQ(raptor.getPrimaryCannon().getRelativePosition(), sf::Vector2f(0, 0));
}

TEST(RaptorTest, shield) {
    float time = 4;
    Raptor raptor;
    sf::RectangleShape r;
    r.setScale(sf::Vector2f(1, 1));
    raptor.useShield(time, r);
    ASSERT_EQ(raptor.isCharging(), false);
    raptor.useShield(time, r);
    ASSERT_EQ(raptor.isCharging(), true);
    ASSERT_EQ(raptor.getShield().getScale(), sf::Vector2f(0, 0));
    raptor.recharge(rechargeTime / 1.5, r);
    ASSERT_EQ(raptor.isCharging(), true);
    ASSERT_EQ(raptor.getShield().getScale(), sf::Vector2f(0, 0));
    raptor.recharge(rechargeTime / 1.5, r);
    ASSERT_EQ(raptor.isCharging(), false);
    ASSERT_EQ(raptor.getShield().getScale(), sf::Vector2f(1, 1));
}

TEST(BomberTest, bomb) {
    Bomber bomber;
    sf::RectangleShape r;
    bomber.useBomb(r);
    ASSERT_EQ(bomber.isCharging(), true);
    bomber.recharge(1.f / (bomber.getSecondaryCannon().getSpaceshipPtr()->getFireRate() *
                           bomber.getSecondaryCannon().getFireRateMultiplier()) - 1, r);
    ASSERT_EQ(bomber.isCharging(), true);
    bomber.recharge(2, r);
    ASSERT_EQ(bomber.isCharging(), false);

}