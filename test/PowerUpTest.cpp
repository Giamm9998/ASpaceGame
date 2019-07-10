//
// Created by gianmarco on 09/07/19.
//
#include "gtest/gtest.h"
#include "../AuxiliaryCannon.h"
#include "../Raptor.h"
#include "../Bomber.h"
#include "../EnhanceSpecial.h"
#include "../FireRate.h"
#include "../FullHealth.h"
#include "../LaserCannon.h"
#include "../Speed.h"
#include "../Strength.h"

TEST(AuxiliaryCannonTest, powerUp) {
    Raptor raptor;
    Bomber bomber;
    AuxiliaryCannon auxiliaryCannon;

    auxiliaryCannon.powerUp(raptor);
    ASSERT_EQ(raptor.getAuxiliaryCannons().size(), 1);
    ASSERT_EQ(raptor.getAuxiliaryCannons()[0].getRelativePosition(), sf::Vector2f(76, 0));
    ASSERT_EQ(raptor.getPrimaryCannon().getRelativePosition(), sf::Vector2f(-76, 0));

    auxiliaryCannon.powerUp(bomber);
    ASSERT_EQ(bomber.getAuxiliaryCannons().size(), 1);
    ASSERT_EQ(bomber.getAuxiliaryCannons()[0].getRelativePosition(), sf::Vector2f(106, 0));
    ASSERT_EQ(bomber.getPrimaryCannon().getRelativePosition(), sf::Vector2f(-106, 0));

    auxiliaryCannon.powerUp(raptor);
    ASSERT_EQ(raptor.getAuxiliaryCannons().size(), 2);
    ASSERT_EQ(raptor.getAuxiliaryCannons()[0].getRelativePosition(), sf::Vector2f(76, 0));
    ASSERT_EQ(raptor.getPrimaryCannon().getRelativePosition(), sf::Vector2f(-76, 0));
    ASSERT_EQ(raptor.getAuxiliaryCannons()[1].getRelativePosition(), sf::Vector2f(0, 0));

    auxiliaryCannon.powerUp(bomber);
    ASSERT_EQ(bomber.getAuxiliaryCannons().size(), 2);
    ASSERT_EQ(bomber.getAuxiliaryCannons()[0].getRelativePosition(), sf::Vector2f(106, 0));
    ASSERT_EQ(bomber.getPrimaryCannon().getRelativePosition(), sf::Vector2f(-106, 0));
    ASSERT_EQ(bomber.getAuxiliaryCannons()[1].getRelativePosition(), sf::Vector2f(0, 0));

    auxiliaryCannon.powerUp(raptor);
    ASSERT_EQ(raptor.getAuxiliaryCannons().size(), 2);
    auxiliaryCannon.powerUp(bomber);
    ASSERT_EQ(bomber.getAuxiliaryCannons().size(), 2);
}

TEST(EnhanceSpecialTest, powerUp) {
    Raptor raptor;
    Bomber bomber;
    EnhanceSpecial enhanceSpecial;

    float i = raptor.getShieldDuration();
    enhanceSpecial.powerUp(raptor);
    ASSERT_FLOAT_EQ(raptor.getShieldDuration(), i * 1.5);

    i = bomber.getSecondaryCannon().getFireRateMultiplier();
    enhanceSpecial.powerUp(bomber);
    ASSERT_FLOAT_EQ(bomber.getSecondaryCannon().getFireRateMultiplier(), i * 2);
}

TEST(FireRateTest, powerUp) {
    Raptor raptor;
    FireRate fireRate;

    float i = raptor.getFireRate();
    fireRate.powerUp(raptor);
    ASSERT_FLOAT_EQ(raptor.getFireRate(), i * 10);
}

TEST(FullHealthTest, powerUp) {
    Raptor raptor;
    FullHealth fullHealth;

    raptor.receiveDamage(40);
    ASSERT_EQ(raptor.getHp(), raptor.getMaxHp() - 40);
    fullHealth.powerUp(raptor);
    ASSERT_EQ(raptor.getHp(), raptor.getMaxHp());
}

TEST(LaserCannonTest, powerUp) {
    Raptor raptor;
    LaserCannon laserCannon;

    ASSERT_EQ(raptor.isLaserActive(), false);
    laserCannon.powerUp(raptor);
    ASSERT_EQ(raptor.isLaserActive(), true);
}

TEST(SpeedTest, powerUp) {
    Raptor raptor;
    Speed speed;

    float i = raptor.getSpeed();
    speed.powerUp(raptor);
    ASSERT_FLOAT_EQ(raptor.getSpeed(), i * 1.2);
}

TEST(StrengthTest, powerUp) {
    Raptor raptor;
    Strength strength;

    float i = raptor.getStrength();
    strength.powerUp(raptor);
    ASSERT_FLOAT_EQ(raptor.getStrength(), i * 100);
}