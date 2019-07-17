//
// Created by gianmarco on 10/07/19.
//
#include "gtest/gtest.h"
#include "../EntityManager.h"
#include "../Raptor.h"
#include "../Factory.h"

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
    entityManager.emplaceProjectileTest(std::unique_ptr<Projectile>(new Projectile(0, 0, false)));
    entityManager.getProjectileManager().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition());
    auto projectileIter = entityManager.getProjectileManagerTest().begin();
    entityManager.checkForProjectileCollisionsTest(projectileIter, false);
    ASSERT_FALSE(entityManager.getProjectileManager().empty());
    entityManager.getProjectileManager().front()->getSprite().setPosition(-1000, 0);
    entityManager.checkForProjectileCollisionsTest(projectileIter, false);
    ASSERT_TRUE(entityManager.getProjectileManager().empty());

    entityManager.getPlayer()->setCharging(false);
    entityManager.emplaceProjectileTest(std::unique_ptr<Projectile>(new Projectile(0, 10)));
    entityManager.getProjectileManager().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition());
    projectileIter = entityManager.getProjectileManagerTest().begin();
    entityManager.checkForProjectileCollisionsTest(projectileIter, true);
    ASSERT_TRUE(entityManager.getProjectileManager().empty());
    ASSERT_FLOAT_EQ(entityManager.getPlayer()->getHp(), entityManager.getPlayer()->getMaxHp());
    entityManager.emplaceProjectileTest(std::unique_ptr<Projectile>(new Projectile(0, 10)));
    entityManager.getProjectileManager().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition());
    projectileIter = entityManager.getProjectileManagerTest().begin();
    entityManager.checkForProjectileCollisionsTest(projectileIter, false);
    ASSERT_TRUE(entityManager.getProjectileManager().empty());
    ASSERT_FLOAT_EQ(entityManager.getPlayer()->getHp(), entityManager.getPlayer()->getMaxHp() - 10);

    entityManager.getAsteroidManagerTest().clear(); //todo temporary
    entityManager.getAsteroidManagerTest().emplace_back(new Asteroid);
    entityManager.updateAsteroids(0, false);
    entityManager.emplaceProjectileTest(std::unique_ptr<Projectile>(new Projectile(0, 10, false)));
    entityManager.getProjectileManager().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition());
    projectileIter = entityManager.getProjectileManagerTest().begin();
    entityManager.checkForProjectileCollisionsTest(projectileIter, false);
    ASSERT_FALSE(entityManager.getProjectileManager().empty());
    entityManager.getProjectileManager().front()->getSprite().setPosition(
            entityManager.getAsteroidManager().front()->getSprite().getPosition());
    entityManager.checkForProjectileCollisionsTest(projectileIter, false);
    ASSERT_TRUE(entityManager.getProjectileManager().empty());
    ASSERT_FLOAT_EQ (entityManager.getAsteroidManager().front()->getHp(),
                     (asteroidMaxHp / asteroidMaxSize * entityManager.getAsteroidManager().front()->getSize()) - 10);
    entityManager.emplaceProjectileTest(std::unique_ptr<Projectile>(new Projectile(0, 10, false)));
    entityManager.getAsteroidManagerTest().front()->receiveDamage(1000);
    entityManager.getProjectileManager().front()->getSprite().setPosition(
            entityManager.getAsteroidManager().front()->getSprite().getPosition());
    entityManager.checkForProjectileCollisionsTest(projectileIter, false);
    ASSERT_FALSE(entityManager.getProjectileManager().empty());
    entityManager.getProjectileManagerTest().clear();


    entityManager.getEnemyManagerTest().clear(); //todo temporary
    entityManager.getEnemyManagerTest().emplace_back(Factory::createEnemy(EnemyType::Fighter));
    entityManager.updateEnemies(0);
    entityManager.emplaceProjectileTest(std::unique_ptr<Projectile>(new Projectile(0, 10, false)));
    entityManager.getProjectileManager().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition());
    projectileIter = entityManager.getProjectileManagerTest().begin();
    entityManager.checkForProjectileCollisionsTest(projectileIter, false);
    ASSERT_FALSE(entityManager.getProjectileManager().empty());
    entityManager.getProjectileManager().front()->getSprite().setPosition(
            entityManager.getEnemyManager().front()->getSprite().getPosition());
    entityManager.checkForProjectileCollisionsTest(projectileIter, false);
    ASSERT_TRUE(entityManager.getProjectileManager().empty());
    ASSERT_FLOAT_EQ (entityManager.getEnemyManager().front()->getHp(),
                     entityManager.getEnemyManager().front()->getMaxHp() - 10);
}

TEST(EntityManagerTest, asteroidCollision) {
    EntityManager entityManager;
    entityManager.selectPlayer<Raptor>();
    entityManager.getAsteroidManagerTest().clear(); //todo temporary
    entityManager.getAsteroidManagerTest().emplace_back(new Asteroid);
    entityManager.getAsteroidManagerTest().front()->getSprite().setPosition(0, 0);
    auto asteroidIter = entityManager.getAsteroidManagerTest().begin();
    entityManager.checkForAsteroidCollisionsTest(asteroidIter, false);
    ASSERT_FALSE(entityManager.getAsteroidManager().empty());
    entityManager.getAsteroidManager().front()->getSprite().setPosition(0, 2000);
    entityManager.checkForAsteroidCollisionsTest(asteroidIter, false);
    ASSERT_TRUE(entityManager.getAsteroidManager().empty());

    entityManager.getPlayer()->setCharging(false);
    entityManager.getAsteroidManagerTest().emplace_back(new Asteroid);
    entityManager.getAsteroidManager().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition());
    asteroidIter = entityManager.getAsteroidManagerTest().begin();
    entityManager.checkForAsteroidCollisionsTest(asteroidIter, true);
    ASSERT_TRUE(entityManager.getAsteroidManager().empty());
    ASSERT_FLOAT_EQ(entityManager.getPlayer()->getHp(), entityManager.getPlayer()->getMaxHp());
    entityManager.getAsteroidManagerTest().emplace_back(new Asteroid);
    entityManager.getAsteroidManager().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition());
    asteroidIter = entityManager.getAsteroidManagerTest().begin();
    entityManager.getAsteroidManager().front()->getSprite().setScale(
            sf::Vector2f(1, 1) * entityManager.getAsteroidManager().front()->getSize());
    auto damage = entityManager.getAsteroidManager().front()->getDamage();
    entityManager.checkForAsteroidCollisionsTest(asteroidIter, false);
    ASSERT_TRUE(entityManager.getAsteroidManager().empty());
    ASSERT_FLOAT_EQ(entityManager.getPlayer()->getHp(), entityManager.getPlayer()->getMaxHp() - damage);
}

TEST(EntityManagerTest, laserCollision) {
    EntityManager entityManager;
    entityManager.selectPlayer<Raptor>();
    entityManager.getEnemyManagerTest().clear(); //todo temporary
    entityManager.getEnemyManagerTest().emplace_back(Factory::createEnemy(EnemyType::Minion));
    entityManager.getEnemyManagerTest().front()->getSprite().setPosition(0, 0);
    entityManager.updateEnemies(0);
    entityManager.getAsteroidManagerTest().clear(); //todo temporary
    entityManager.getAsteroidManagerTest().emplace_back(new Asteroid);
    entityManager.getAsteroidManagerTest().front()->getSprite().setPosition(0, 0);
    entityManager.getAsteroidManager().front()->getSprite().setScale(
            sf::Vector2f(1, 1) * entityManager.getAsteroidManager().front()->getSize());
    entityManager.checkForLaserCollisionTest(0.2);
    ASSERT_FLOAT_EQ(entityManager.getEnemyManager().front()->getHp(),
                    entityManager.getEnemyManager().front()->getMaxHp());
    ASSERT_FLOAT_EQ(entityManager.getAsteroidManager().front()->getHp(),
                    (asteroidMaxHp / asteroidMaxSize * entityManager.getAsteroidManager().front()->getSize()));
    entityManager.getEnemyManagerTest().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition().y, 0);
    entityManager.updateEnemies(0);
    entityManager.getAsteroidManagerTest().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition().y, 0);
    entityManager.checkForLaserCollisionTest(0.2);
    ASSERT_FLOAT_EQ(entityManager.getEnemyManager().front()->getHp(),
                    entityManager.getEnemyManager().front()->getMaxHp() - laserDPS * 0.2);
    ASSERT_FLOAT_EQ(entityManager.getAsteroidManager().front()->getHp(),
                    (asteroidMaxHp / asteroidMaxSize * entityManager.getAsteroidManager().front()->getSize()) -
                    laserDPS * 0.2);
}

//todo test update