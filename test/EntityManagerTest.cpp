//
// Created by gianmarco on 10/07/19.
//
#include "gtest/gtest.h"
#include "../EntityManager.h"
#include "../Raptor.h"

TEST(EntityManagerTest, Constructor) {
    EntityManager entityManager;
    ASSERT_TRUE(entityManager.getProjectileManager().empty());
    //ASSERT_TRUE(entityManager.getEnemyManager().empty());
    //ASSERT_TRUE(entityManager.getAsteroidManager().empty());
    ASSERT_TRUE(entityManager.getPlayer() == nullptr);
}

TEST(EntityManagerTest, shots) {
    EntityManager entityManager;
    entityManager.selectPlayer<Raptor>();
    entityManager.updateEnemies(10);
    ASSERT_FALSE(entityManager.getProjectileManager().empty());
    sf::RectangleShape a;
    sf::RectangleShape b;
    entityManager.updatePlayer(10, false, false, true, false, a, b);
    ASSERT_FALSE(entityManager.getProjectileManager().empty());
}

TEST(EntityManagerTest, isOutOfSigth) {
    Raptor raptor;
    raptor.getSprite().move(-2000, 0);
    ASSERT_TRUE(EntityManager::isOutOfSigth(raptor.getSprite()));
    raptor.getSprite().move(4000, 0);
    ASSERT_TRUE(EntityManager::isOutOfSigth(raptor.getSprite()));
    raptor.getSprite().move(-2000, 0);
    raptor.getSprite().move(0, 2000);
    ASSERT_TRUE(EntityManager::isOutOfSigth(raptor.getSprite()));
    raptor.getSprite().move(0, -4000);
    ASSERT_TRUE(EntityManager::isOutOfSigth(raptor.getSprite()));
}

TEST(EntityManagerTest, projectileCollision) {
    EntityManager entityManager;
    entityManager.selectPlayer<Raptor>();
    entityManager.updateEnemies(0);
    entityManager.emplaceProjectileTest(std::unique_ptr<Projectile>(new Projectile(0, 0, false)));
    entityManager.getProjectileManager().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition());
    auto projectileIter = entityManager.getProjectileManagerTest().begin();
    entityManager.checkForProjectileCollisionsTest(projectileIter, false);
    ASSERT_FALSE(entityManager.getProjectileManager().empty());
    entityManager.getProjectileManager().front()->getSprite().setPosition(
            entityManager.getEnemyManager().front()->getSprite().getPosition());
    entityManager.checkForProjectileCollisionsTest(projectileIter, false);
    ASSERT_TRUE(entityManager.getProjectileManager().empty());
}