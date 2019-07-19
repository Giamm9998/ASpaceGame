//
// Created by gianmarco on 10/07/19.
//
#include "gtest/gtest.h"
#include "../EntityManager.h"
#include "../Raptor.h"
#include "../Factory.h"
#include "../Game.h"

TEST(EntityManagerTest, Constructor) {
    EntityManager entityManager;
    ASSERT_TRUE(entityManager.getProjectileManager().empty());
    ASSERT_TRUE(entityManager.getEnemyManager().empty());
    ASSERT_TRUE(entityManager.getAsteroidManager().empty());
    ASSERT_EQ(entityManager.getScore(), 0);
    ASSERT_EQ(entityManager.getDestroyedAsteroids(), 0);
    ASSERT_EQ(entityManager.getKilledSpaceships(), 0);
    ASSERT_EQ(entityManager.getKilledBosses(), 0);
    ASSERT_EQ(entityManager.getPlayer(), nullptr);
    ASSERT_EQ(entityManager.getPowerUp(), nullptr);
}

TEST(EntityManagerTest, shots) {
    EntityManager entityManager;
    entityManager.selectPlayer<Raptor>();
    entityManager.updateEnemies(10);
    ASSERT_TRUE(entityManager.getProjectileManager().empty());
    entityManager.getEnemyManagerTest().emplace_back(Factory::createEnemy(EnemyType::Minion));
    entityManager.updateEnemies(10);
    ASSERT_FALSE(entityManager.getProjectileManager().empty());
    entityManager.getEnemyManagerTest().clear();
    sf::RectangleShape a;
    sf::RectangleShape b;
    entityManager.updatePlayer(10, false, false, true, false, a, b);
    ASSERT_FALSE(entityManager.getProjectileManager().empty());
}

TEST(EntityManagerTest, isOutOfSigth) {
    Raptor raptor;
    raptor.getSprite().move(-2000, 0);
    ASSERT_TRUE(EntityManager::isOutOfSight(raptor.getSprite()));
    raptor.getSprite().move(4000, 0);
    ASSERT_TRUE(EntityManager::isOutOfSight(raptor.getSprite()));
    raptor.getSprite().move(-2000, 0);
    raptor.getSprite().move(0, 2000);
    ASSERT_TRUE(EntityManager::isOutOfSight(raptor.getSprite()));
    raptor.getSprite().move(0, -4000);
    ASSERT_TRUE(EntityManager::isOutOfSight(raptor.getSprite()));
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
    ASSERT_FALSE(entityManager.getProjectileManager().empty());
    auto time = 0.001;
    while (time <= 2 * enemySpawnDuration) {
        entityManager.updateEnemies(time);
        time += 0.001;
    }
    entityManager.getProjectileManagerTest().clear();
    entityManager.emplaceProjectileTest(std::unique_ptr<Projectile>(new Projectile(0, 10, false)));
    entityManager.getProjectileManager().front()->getSprite().setPosition(
            entityManager.getEnemyManager().front()->getSprite().getPosition());
    projectileIter = entityManager.getProjectileManagerTest().begin();
    entityManager.checkForProjectileCollisionsTest(projectileIter, false);
    ASSERT_TRUE(entityManager.getProjectileManager().empty());
    ASSERT_FLOAT_EQ (entityManager.getEnemyManager().front()->getHp(),
                     entityManager.getEnemyManager().front()->getMaxHp() - 10);
}

TEST(EntityManagerTest, asteroidCollision) {
    EntityManager entityManager;
    entityManager.selectPlayer<Raptor>();
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
    entityManager.getEnemyManagerTest().emplace_back(Factory::createEnemy(EnemyType::Minion));
    entityManager.getEnemyManagerTest().front()->getSprite().setPosition(0, 0);
    auto time = 0.001;
    while (time <= 2 * enemySpawnDuration) {
        entityManager.updateEnemies(time);
        time += 0.001;
    }
    entityManager.getAsteroidManagerTest().emplace_back(new Asteroid);
    entityManager.getAsteroidManagerTest().front()->getSprite().setPosition(0, 0);
    entityManager.getAsteroidManager().front()->getSprite().setScale(
            sf::Vector2f(1, 1) * entityManager.getAsteroidManager().front()->getSize());
    entityManager.getPlayer()->setLaserActive(true);
    entityManager.getPlayer()->getLaser().setPosition(entityManager.getPlayer()->getSprite().getPosition());
    entityManager.checkForLaserCollisionTest(0.2);
    ASSERT_FLOAT_EQ(entityManager.getEnemyManager().front()->getHp(),
                    entityManager.getEnemyManager().front()->getMaxHp());
    ASSERT_FLOAT_EQ(entityManager.getAsteroidManager().front()->getHp(),
                    (asteroidMaxHp / asteroidMaxSize * entityManager.getAsteroidManager().front()->getSize()));
    entityManager.getEnemyManagerTest().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition().x, 0);
    entityManager.updateEnemies(0);
    entityManager.getAsteroidManagerTest().front()->getSprite().setPosition(
            entityManager.getPlayer()->getSprite().getPosition().x, 0);
    entityManager.checkForLaserCollisionTest(0.2);
    ASSERT_FLOAT_EQ(entityManager.getEnemyManager().front()->getHp(),
                    entityManager.getEnemyManager().front()->getMaxHp() - laserDPS * 0.2);
    ASSERT_FLOAT_EQ(entityManager.getAsteroidManager().front()->getHp(),
                    (asteroidMaxHp / asteroidMaxSize * entityManager.getAsteroidManager().front()->getSize()) -
                    laserDPS * 0.2);
}

TEST(EntityManagerTest, death) {
    EntityManager entityManager;
    entityManager.selectPlayer<Raptor>();
    entityManager.getEnemyManagerTest().emplace_back(Factory::createEnemy(EnemyType::Minion));
    entityManager.getEnemyManagerTest().emplace_back(Factory::createEnemy(EnemyType::Assaulter));
    entityManager.getEnemyManagerTest().emplace_back(Factory::createEnemy(EnemyType::Fighter));
    for (auto &enemy : entityManager.getEnemyManager()) {
        enemy->receiveDamage(10);
    }
    entityManager.updateEnemies(5);
    ASSERT_FALSE(entityManager.getEnemyManager().empty());
    for (auto &enemy : entityManager.getEnemyManager()) {
        enemy->receiveDamage(500);
    }
    entityManager.updateEnemies(5);
    ASSERT_TRUE(entityManager.getEnemyManager().empty());

    for (int i = 0; i < 10; i++) {
        entityManager.getAsteroidManagerTest().emplace_back(new Asteroid);
    }
    for (auto &asteroid : entityManager.getAsteroidManager()) {
        asteroid->receiveDamage(5);
    }
    entityManager.updateAsteroids(5, false);
    ASSERT_FALSE(entityManager.getAsteroidManager().empty());
    for (auto &asteroid : entityManager.getAsteroidManager()) {
        asteroid->receiveDamage(500);
    }
    entityManager.updateAsteroids(5, false);
    ASSERT_TRUE(entityManager.getAsteroidManager().empty());
}
