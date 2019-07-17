//
// Created by Fabio Luccioletti on 2019-07-10.
//

#include <cmath>
#include <iostream>
#include "EntityManager.h"
#include "Fighter.h"
#include "Kamikaze.h"
#include "Minion.h"
#include "Assaulter.h"
#include "Boss.h"
#include "Raptor.h"
#include "LaserCannon.h"
#include "FireRate.h"
#include "AuxiliaryCannon.h"
#include "Bomber.h"
#include "ResourceManager.h"
#include "Factory.h"
#include "Functions.h"
#include "FullHealth.h"
#include "EnhanceSpecial.h"

EntityManager::EntityManager() : killedBosses(0), killedSpaceships(0), destroyedAsteroids(0), score(0) {

    createSounds();
}

const std::unique_ptr<Player> &EntityManager::getPlayer() const {
    return player;
}

const std::list<std::unique_ptr<Spaceship>> &EntityManager::getEnemyManager() const {
    return enemyManager;
}

const std::list<std::unique_ptr<Projectile>> &EntityManager::getProjectileManager() const {
    return projectileManager;
}

const std::list<std::unique_ptr<Asteroid>> &EntityManager::getAsteroidManager() const {
    return asteroidManager;
}

const std::unique_ptr<PowerUp> &EntityManager::getPowerUp() const {
    return powerUp;
}

void EntityManager::updateSpawn(float time) {
    int enemiesOnScreen = getEnemyManager().size();
    int asteroidsOnScreen = getAsteroidManager().size();
    asteroidSpawnGap += time;
    if (!bossMode) {
        if (mainTheme.getStatus() == sf::Sound::Stopped && bossEnd.getStatus() == sf::Sound::Stopped)
            mainTheme.play();
        enemySpawnGap += time;
        if ((enemiesOnScreen == 0 && enemySpawnGap >= 0) ||
            (enemiesOnScreen < maxEnemiesOnScreen && enemySpawnGap > minEnemySpawnGap)) {
            enemySpawnGap = 0;
            enemyManager.emplace_back(Factory::createEnemy(getRandomEnemy(3, 1, 1, 1)));
        }

        if (asteroidsOnScreen < maxAsteroidsOnScreen && asteroidSpawnGap > nextAsteroidSpawnGap) {
            asteroidManager.emplace_back(new Asteroid);
            asteroidSpawnGap = 0;
            nextAsteroidSpawnGap = getRandomReal(0, maxAsteroidSpawnGap);
        }

        if (powerUp == nullptr && score > nextPowerUpSpawnScore) {
            powerUp = Factory::createPowerUp(
                    getRandomPowerUp(1, 0, player->getHp() == player->getMaxHp(), player->isLaserActive(),
                                     player->getAuxiliaryCannons().size() == 2));
            nextPowerUpSpawnScore += getRandomInt(maxPowerUpSpawnScore - 200, maxPowerUpSpawnScore);
        }

        if (score > 500 && score <= 1000) {
            maxEnemiesOnScreen = 3;
            minEnemySpawnGap = 6;
            maxAsteroidSpawnGap = 25;
            maxPowerUpSpawnScore = 800;
        } else if (score > 1000 && score <= 3000) {
            maxEnemiesOnScreen = 4;
            minEnemySpawnGap = 5;
            maxAsteroidsOnScreen = 3;
            maxAsteroidSpawnGap = 20;
            maxPowerUpSpawnScore = 900;
        } else if (score > 3000 && score <= 5000) {
            maxEnemiesOnScreen = 4;
            minEnemySpawnGap = 4;
            maxAsteroidsOnScreen = 3;
            maxAsteroidSpawnGap = 15;
            maxPowerUpSpawnScore = 1100;
        } else if (score > nextBossSpawnScore) {
            bossMode = true;
        } else if (score > 5000 && score < 10000) {
            maxEnemiesOnScreen = 5;
            minEnemySpawnGap = 3.5;
            maxAsteroidsOnScreen = 4;
            maxAsteroidSpawnGap = 12;
            maxPowerUpSpawnScore = 1300;
        } else if (score > 10000 && score < 15000) {
            maxEnemiesOnScreen = 6;
            minEnemySpawnGap = 3;
            maxAsteroidsOnScreen = 5;
            maxAsteroidSpawnGap = 10;
            maxPowerUpSpawnScore = 1600;
        } else if (score > 15000) {
            maxEnemiesOnScreen = 6;
            minEnemySpawnGap = 2.5;
            maxAsteroidsOnScreen = 6;
            maxAsteroidSpawnGap = 8;
            maxPowerUpSpawnScore = 2000;
        }
    } else {
        if (!bossKilled) {
            if (enemiesOnScreen == 0) {
                mainTheme.stop();
                bossBegin.play();
                enemyManager.emplace_back(Factory::createEnemy(EnemyType::Boss));
                bossAttackTime = 10;
                bossCurrentAttack.clear();
                enemyManager.front()->setHp(3000 * (1 + killedBosses));
            }
            if (bossMiddle.getStatus() != sf::Sound::Playing && typeid(*enemyManager.front().get()) == typeid(Boss) &&
                bossBegin.getStatus() == sf::Sound::Stopped) //todo
                bossMiddle.play();

            if (asteroidsOnScreen < (maxAsteroidsOnScreen + killedBosses) && asteroidSpawnGap > nextAsteroidSpawnGap) {
                asteroidManager.emplace_back(new Asteroid);
                asteroidSpawnGap = 0;
                nextAsteroidSpawnGap = getRandomReal(0, maxAsteroidSpawnGap / (killedBosses + 1));
            }
        } else {
            bossMiddle.stop();
            bossEnd.play();
            powerUp = Factory::createPowerUp(
                    getRandomPowerUp(0, 1, player->getHp() == player->getMaxHp(), player->isLaserActive(),
                                     player->getAuxiliaryCannons().size() == 2));
            asteroidSpawnGap = -10;
            enemySpawnGap = -10;
            nextPowerUpSpawnScore = score + getRandomInt(maxPowerUpSpawnScore - 200, maxPowerUpSpawnScore);
            bossMode = false;
            bossKilled = false;
            nextBossSpawnScore = score + 5000;
        }
    }

}

void EntityManager::updatePowerUp(float time, sf::RectangleShape &hpHud, sf::RectangleShape &specialHud) {
    if (powerUp != nullptr) {
        powerUp->getAnimator()->update(time);
        powerUp->move(time);
        if (EntityManager::isOutOfSigth(powerUp->getSprite())) {
            powerUp.reset();
        } else if (powerUp->getSprite().getGlobalBounds().intersects(player->getBoundingBox().getGlobalBounds())) {
            auto &playerType = *(player.get());
            auto &powerUpType = *(powerUp.get());
            if (typeid(powerUpType) == typeid(FullHealth))
                hpHud.setScale(1, 1);
            if (typeid(powerUpType) == typeid(EnhanceSpecial) && typeid(playerType) == typeid(Raptor))
                specialHud.setScale(1, 1);
            powerUp->powerUp(*player);
            powerUp.reset();
        }
    }
}

void EntityManager::updatePlayer(float time, bool isMovingRight, bool isMovingLeft, bool isShooting,
                                 bool isUsingSpecial, sf::RectangleShape &specialHud, sf::RectangleShape &hpHud) {
    if (player->isReceivingDamage()) {
        hpHud.setScale(1, std::max(0.f, (player->getHp() / player->getMaxHp())));
        player->blink(time);
    }
    if (player->getHp() <= 0) {
        if (player->die(time)) {
            mainTheme.stop();
            if (player->isLaserActive())
                player->getLaserSound().stop();
            gameOver.play();
            gameEnded = true;
            player->getBoundingBox().setScale(0, 0);
        }
    }

    if (player->isMovable()) {
        if (isMovingRight)
            player->move(time, right);

        if (isMovingLeft)
            player->move(time, left);

        if (isShooting) {
            emplaceProjectile(player->useCannon(time, (player->getPrimaryCannon())));
            for (auto &auxiliaryCannon : player->getAuxiliaryCannons())
                emplaceProjectile(player->useCannon(time, auxiliaryCannon));
        }

        if (isUsingSpecial) {
            auto &playerType = *(player.get());
            if (typeid(playerType) == typeid(Bomber)) {
                if (!player->isCharging())
                    emplaceProjectile(dynamic_cast<Bomber &>(*player).useBomb(specialHud));
            }
            if (typeid(playerType) == typeid(Raptor)) {
                if (!player->isCharging()) {
                    if (!shieldActive) {
                        shieldSound.play();
                        shieldActive = true;
                    }
                    dynamic_cast<Raptor &>(*player).useShield(time, specialHud);
                }
            }
        } else shieldActive = false;
        if (player->isCharging()) //exploit late binding
            player->recharge(time, specialHud);

        if (player->isLaserActive()) {
            player->getLaserAnimator()->update(time);
            checkForLaserCollision(time);
        }
    } else if (finalMovementTime <= finalMovementDuration) {
        finalMovementTime += time;
        player->getSprite().move(finalMovement * (time / finalMovementDuration));
    }
}

void EntityManager::updateEnemies(float time) {
    for (auto enemyIter = enemyManager.begin(); enemyIter != enemyManager.end();) {
        auto enemy = (*enemyIter).get();
        if ((enemy)->getHp() <= 0) {
            if (typeid(*enemy) == typeid(Kamikaze) && enemy->getDyingTime() == 0) {
                if (enemy->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
                    player->receiveDamage(200);
                }
                for (auto otherEnemyIter = enemyManager.begin(); otherEnemyIter != enemyManager.end(); otherEnemyIter++)
                    if (otherEnemyIter != enemyIter) {
                        if (enemy->getSprite().getGlobalBounds().intersects(
                                (*otherEnemyIter)->getSprite().getGlobalBounds())) {
                            (*otherEnemyIter)->receiveDamage(200);
                        }
                    }
                for (auto &asteroidIter : asteroidManager) //todo test if works in game
                    if (enemy->getSprite().getGlobalBounds().intersects(
                            asteroidIter->getSprite().getGlobalBounds())) {
                        asteroidIter->receiveDamage(200);
                    }
            }
            if ((enemy)->die(time)) {
                killedSpaceships++;
                if (typeid(*enemy) == typeid(Boss)) {
                    killedBosses++;
                    bossKilled = true;
                }
                score += static_cast<int>(enemy->getMaxHp());
                notify();
                enemyManager.erase(enemyIter++);
            } else
                enemyIter++;
        } else {
            if ((enemy)->isReceivingDamage())
                (enemy)->blink(time);

            enemy->move(time);
            if (typeid(*enemy) == typeid(Assaulter)) {
                emplaceProjectile(dynamic_cast<Assaulter &>(*enemy).useCannon(
                        time, enemy->getPrimaryCannon(), player->getSprite().getPosition()));
            } else if (typeid(*enemy) == typeid(Fighter)) {
                emplaceProjectile(enemy->useCannon(time, enemy->getPrimaryCannon()));
                for (auto &externalCannon : dynamic_cast<Fighter &>(*(enemy)).getExternalCannons())
                    emplaceProjectile(enemy->useCannon(time, externalCannon));
            } else if (typeid(*enemy) == typeid(Boss)) {
                bossAttackTime += time;
                if (bossAttackTime >= 10 + bossSpawnDuration) {
                    bossAttackTime = bossSpawnDuration;
                    bossCurrentAttack = dynamic_cast<Boss &>(*(enemy)).chooseAttack();
                }
                for (auto &cannon: bossCurrentAttack) {
                    if (cannon->isTracker()) {
                        emplaceProjectile(dynamic_cast<Boss &>(*(enemy)).useCannon(time, *cannon,
                                                                                   player->getSprite().getPosition()));
                    } else if (cannon->getFireRateMultiplier() == 1.8f) {
                        emplaceProjectile(dynamic_cast<Boss &>(*(enemy)).useMobileCannon(time, *cannon));
                    } else emplaceProjectile(enemy->useCannon(time, *cannon));
                }
            } else if (typeid(*enemy) == typeid(Kamikaze)) {
                if (dynamic_cast<Kamikaze &>(*(enemy)).isAttacking() && player->isMovable())
                    checkForAttractingBeamCollision(enemyIter);
            } else
                emplaceProjectile(enemy->useCannon(time, enemy->getPrimaryCannon()));
            enemyIter++;
        }
    }

}

void EntityManager::updateAsteroids(float time, bool isUsingSpecial) {
    for (auto asteroidIter = asteroidManager.begin(); asteroidIter != asteroidManager.end();) {
        auto asteroid = (*asteroidIter).get();
        if ((asteroid)->getHp() <= 0) {
            if ((asteroid)->die(time)) {
                destroyedAsteroids++;
                score += static_cast<int>(asteroid->getStartingHp());
                notify();
                asteroidManager.erase(asteroidIter++);
            } else
                asteroidIter++;
        } else {
            if ((asteroid)->isReceivingDamage())
                (asteroid)->blink(time);
            (asteroid)->getAnimator()->update(time);
            (asteroid)->move(time);
            checkForAsteroidCollisions(asteroidIter++, isUsingSpecial);
        }
    }
}

void EntityManager::updateProjectiles(float time, bool isUsingSpecial) {
    for (auto projectileIter = projectileManager.begin(); projectileIter != projectileManager.end();) {
        (*projectileIter)->move(time);
        checkForProjectileCollisions(projectileIter++, isUsingSpecial);
    }
}

void EntityManager::checkForProjectileCollisions(std::list<std::unique_ptr<Projectile>>::iterator projectileIter,
                                                 bool isUsingSpecial) {
    sf::Sprite &projSprite = (*projectileIter)->getSprite();
    if (isOutOfSigth(projSprite)) {
        projectileManager.erase(projectileIter);
        return;
    }

    if ((*projectileIter)->isEvil()) {
        auto &playerType = *player;
        if (typeid(playerType) == typeid(Raptor))
            if (isUsingSpecial && !player->isCharging()) {
                auto shield = dynamic_cast<Raptor &>(*player).getShield();
                if (dist(projSprite.getPosition(), shield.getPosition()) <=
                    (shield.getRadius() + projSprite.getGlobalBounds().height / 2)) {
                    projectileManager.erase(projectileIter);
                    return;
                }
            }

        if (player->getBoundingBox().getGlobalBounds().intersects((projSprite.getGlobalBounds()))) {
            player->receiveDamage((*projectileIter)->getDamage());
            projectileManager.erase(projectileIter);
            return;
        }
    } else {
        for (auto &asteroid : asteroidManager) {
            if (asteroid->getHp() > 0) {
                if (dist(asteroid->getSprite().getPosition(), projSprite.getPosition()) <=
                    (asteroidLocalRadius * asteroid->getSprite().getScale().x +
                     projSprite.getGlobalBounds().height / 2)) {
                    asteroid->receiveDamage((*projectileIter)->getDamage());
                    projectileManager.erase(projectileIter);
                    return;
                }
            }
        }
        for (auto &enemy : enemyManager) {
            if (enemy->getBoundingBox().getGlobalBounds().intersects((projSprite.getGlobalBounds()))) {
                if (enemy->getElapsedTime() >= 0)
                    enemy->receiveDamage((*projectileIter)->getDamage());
                projectileManager.erase(projectileIter);
                return;
            }
        }
    }
}

void EntityManager::checkForAsteroidCollisions(std::list<std::unique_ptr<Asteroid>>::iterator asteroidIter,
                                               bool isUsingSpecial) {
    sf::Sprite &asteroidSprite = (*asteroidIter)->getSprite();
    if (isOutOfSigth(asteroidSprite)) {
        asteroidManager.erase(asteroidIter);
        return;
    }

    auto &playerType = *player;
    if (typeid(playerType) == typeid(Raptor))
        if (isUsingSpecial && !player->isCharging()) {
            auto shield = dynamic_cast<Raptor &>(*player).getShield();
            if (dist(asteroidSprite.getPosition(), shield.getPosition()) <=
                (shield.getRadius() + asteroidLocalRadius * (*asteroidIter)->getSize())) {
                asteroidManager.erase(asteroidIter);
                return;
            }
        }

    if (player->getBoundingBox().getGlobalBounds().intersects((asteroidSprite.getGlobalBounds()))) {
        player->receiveDamage((*asteroidIter)->getDamage());
        asteroidManager.erase(asteroidIter);
        return;
    }
}

void EntityManager::checkForLaserCollision(float time) {
    for (auto &enemy : enemyManager) {
        if (enemy->getBoundingBox().getGlobalBounds().intersects((player->getLaser().getGlobalBounds()))) {
            enemy->receiveDamage(laserDPS * time);
        }
    }

    for (auto &asteroid : asteroidManager) {
        if (asteroid->getSprite().getGlobalBounds().intersects(player->getLaser().getGlobalBounds()))
            asteroid->receiveDamage(laserDPS * time);
    }
}

void EntityManager::checkForAttractingBeamCollision(std::list<std::unique_ptr<Spaceship>>::iterator enemyIter) {
    auto kamikaze = (*enemyIter).get();

    if (dynamic_cast<Kamikaze &>(*kamikaze).getBeam().getGlobalBounds().intersects(
            player->getBoundingBox().getGlobalBounds())) {
        player->getBoundingBox().setSize(sf::Vector2f(0, 0));
        player->setMovable(false);
        dynamic_cast<Kamikaze &>(*kamikaze).setTargetAcquired(true);
        if (player->isLaserActive()) {
            player->getLaserSound().stop();
            player->setLaserActive(false);
        }
        auto finalPosition = kamikaze->getSprite().getPosition() +
                             sf::Vector2f(0, kamikaze->getSprite().getOrigin().y * kamikaze->getSprite().getScale().y);
        finalMovement = finalPosition - player->getSprite().getPosition();
    }
}

void EntityManager::emplaceProjectile(std::unique_ptr<Projectile> projectile) {
    if (projectile != nullptr) {
        projectileManager.emplace_back(new Projectile(*projectile));
        if (!projectile->isEvil()) {
            if (projectile->getSize().x != bombSize)
                shotSound.play();
            else
                bombSound.play();
        }
    }
}

float EntityManager::dist(const sf::Vector2f &pointA, const sf::Vector2f &pointB) {
    return sqrt(pow(pointB.x - pointA.x, 2) + pow(pointB.y - pointA.y, 2));
}

bool EntityManager::isOutOfSigth(const sf::Sprite &sprite) {
    return sprite.getPosition().y + sprite.getOrigin().y < 0 ||
           sprite.getPosition().y - sprite.getOrigin().y > windowHeight ||
           sprite.getPosition().x + sprite.getOrigin().x < 0 ||
           sprite.getPosition().x - sprite.getOrigin().x > windowWidth;
}

void EntityManager::createSounds() {
    shotSound.setBuffer(ResourceManager::getSoundBuffer("../sound/shot.wav"));
    shotSound.setVolume(20);
    bombSound.setBuffer(ResourceManager::getSoundBuffer("../sound/bomb.wav"));
    bombSound.setVolume(20);
    mainTheme.setBuffer(ResourceManager::getSoundBuffer("../sound/Music.wav"));
    mainTheme.setLoop(true);
    mainTheme.setVolume(70);
    shieldSound.setBuffer(ResourceManager::getSoundBuffer("../sound/shield.wav"));
    shieldSound.setVolume(60);
    mainTheme.play();
    gameOver.setBuffer(ResourceManager::getSoundBuffer("../sound/gameOver.wav"));
    gameOver.setVolume(50);
    bossBegin.setBuffer(ResourceManager::getSoundBuffer("../sound/bossBegin.wav"));
    bossMiddle.setBuffer(ResourceManager::getSoundBuffer("../sound/bossMiddle.wav"));
    bossMiddle.setLoop(true);
    bossEnd.setBuffer(ResourceManager::getSoundBuffer("../sound/bossEnd.wav"));

}

void EntityManager::subscribe(Observer *o) {
    observers.push_back(o);
}

void EntityManager::unsubscribe(Observer *o) {
    observers.remove(o);
}

void EntityManager::notify() {
    for (auto &i: observers)
        i->update();
}

unsigned int EntityManager::getDestroyedAsteroids() const {
    return destroyedAsteroids;
}

unsigned int EntityManager::getKilledSpaceships() const {
    return killedSpaceships;
}

unsigned int EntityManager::getKilledBosses() const {
    return killedBosses;
}

int EntityManager::getScore() const {
    return score;
}

sf::Sound &EntityManager::getGameOver() {
    return gameOver;
}

bool EntityManager::isGameEnded() const {
    return gameEnded;
}
