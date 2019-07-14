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

EntityManager::EntityManager() : killedBosses(0), killedSpaceships(0), destroyedAsteroids(0), score(0) {

    //todo add spawn function
    createSounds();

    enemyManager.emplace_back(new Fighter);
    enemyManager.emplace_back(new Kamikaze);
    enemyManager.emplace_back(new Minion);
    enemyManager.emplace_back(new Assaulter);
    enemyManager.emplace_back(new Boss);

    //player = std::unique_ptr<Player>(new Raptor);

    powerUp = std::unique_ptr<PowerUp>(new LaserCannon);

    for (int i = 0; i < 10; i++)
        asteroidManager.emplace_back(new Asteroid);
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

void EntityManager::updatePowerUp(float time) {
    if (powerUp != nullptr) {
        powerUp->getAnimator()->update(time);
        powerUp->move(time);
        if (EntityManager::isOutOfSigth(powerUp->getSprite())) {
            powerUp.reset(new FireRate);
        } else if (powerUp->getSprite().getGlobalBounds().intersects(player->getBoundingBox().getGlobalBounds())) {
            powerUp->powerUp(*player);
            powerUp.reset(new AuxiliaryCannon);
        }
    }
}

void EntityManager::updatePlayer(float time, bool isMovingRight, bool isMovingLeft, bool isShooting,
                                 bool isUsingSpecial, sf::RectangleShape &specialHud, sf::RectangleShape &hpHud) {
    if (player->isReceivingDamage()) {
        player->blink(time);
        hpHud.setScale(1, std::max(0.f, (player->getHp() / player->getMaxHp())));
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
            player->getAnimator()->update(time);
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
            if ((enemy)->die(time)) {
                killedSpaceships++;
                if (typeid(enemy) == typeid(Boss))
                    killedBosses++;
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
                    } else if (cannon->getFireRateMultiplier() == 5) {
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
            checkForAsteroidsCollisions(asteroidIter++, isUsingSpecial);
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
            if (dist(asteroid->getSprite().getPosition(), projSprite.getPosition()) <=
                (asteroidLocalRadius * asteroid->getSprite().getScale().x + projSprite.getGlobalBounds().height / 2)) {
                asteroid->receiveDamage((*projectileIter)->getDamage());
                projectileManager.erase(projectileIter);
                return;
            }
        }
        for (auto &enemy : enemyManager) {
            if (enemy->getBoundingBox().getGlobalBounds().intersects((projSprite.getGlobalBounds()))) {
                enemy->receiveDamage((*projectileIter)->getDamage());
                projectileManager.erase(projectileIter);
                return;
            }
        }
    }
}

void EntityManager::checkForAsteroidsCollisions(std::list<std::unique_ptr<Asteroid>>::iterator asteroidIter,
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

void EntityManager::checkForAttractingBeamCollision(std::list<std::unique_ptr<Spaceship>>::iterator enemyIter) {
    auto kamikaze = (*enemyIter).get();

    if (dynamic_cast<Kamikaze &>(*kamikaze).getBeam().getGlobalBounds().intersects(
            player->getBoundingBox().getGlobalBounds())) {
        player->getBoundingBox().setSize(sf::Vector2f(0, 0));
        player->setMovable(false);
        dynamic_cast<Kamikaze &>(*kamikaze).setTargetAcquired(true);
        player->setLaserActive(false);
        auto finalPosition = kamikaze->getSprite().getPosition() +
                             sf::Vector2f(0, kamikaze->getSprite().getOrigin().y * kamikaze->getSprite().getScale().y);
        finalMovement = finalPosition - player->getSprite().getPosition();
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
    shotSound.setVolume(30);
    bombSound.setBuffer(ResourceManager::getSoundBuffer("../sound/bomb.wav"));
    bombSound.setVolume(30);
    mainTheme.setBuffer(ResourceManager::getSoundBuffer("../sound/Music.wav"));
    mainTheme.setLoop(true);
    shieldSound.setBuffer(ResourceManager::getSoundBuffer("../sound/shield.wav"));
    mainTheme.play();
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

unsigned int EntityManager::getScore() const {
    return score;
}
