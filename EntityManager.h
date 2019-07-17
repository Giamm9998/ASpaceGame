//
// Created by Fabio Luccioletti on 2019-07-10.
//

#ifndef ASPACEGAME_ENTITYMANAGER_H
#define ASPACEGAME_ENTITYMANAGER_H



static const float finalMovementDuration = 3.f;

static int maxEnemiesOnScreen = 2;
static float minEnemySpawnGap = 6;
static int maxAsteroidsOnScreen = 2;
static float maxAsteroidSpawnGap = 30;
static float nextAsteroidSpawnGap = 20;
static int maxPowerUpSpawnScore = 800;
static int nextPowerUpSpawnScore = 200;
static int nextBossSpawnScore = 5000;


#include <list>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Asteroid.h"
#include "PowerUp.h"
#include "Subject.h"
#include "Observer.h"

class EntityManager : public Subject {

public:
    EntityManager();

    const std::unique_ptr<Player> &getPlayer() const;

    const std::list<std::unique_ptr<Spaceship>> &getEnemyManager() const;

    const std::list<std::unique_ptr<Projectile>> &getProjectileManager() const;

    const std::list<std::unique_ptr<Asteroid>> &getAsteroidManager() const;

    const std::unique_ptr<PowerUp> &getPowerUp() const;

    void updateEnemies(float time);

    void updatePlayer(float time, bool isMovingRight, bool isMovingLeft, bool isShooting, bool isUsingSpecial,
                      sf::RectangleShape &specialHud, sf::RectangleShape &hpHud);

    void updateProjectiles(float time, bool isUsingSpecial);

    void updatePowerUp(float time, sf::RectangleShape &hpHud, sf::RectangleShape &specialHud);

    void updateAsteroids(float time, bool isUsingSpecial);

    void updateSpawn(float time);

    static bool isOutOfSigth(const sf::Sprite &sprite);

    void subscribe(Observer *o) override;

    void unsubscribe(Observer *o) override;

    void notify() override;

    unsigned int getDestroyedAsteroids() const;

    unsigned int getKilledSpaceships() const;

    unsigned int getKilledBosses() const;

    int getScore() const;

    template<typename T>
    void selectPlayer() {
        player = std::unique_ptr<Player>(new T);
    }

    sf::Sound &getGameOver();

    bool isGameEnded() const;

private:


    std::unique_ptr<Player> player;
    std::list<std::unique_ptr<Spaceship>> enemyManager;
    std::list<std::unique_ptr<Projectile>> projectileManager;
    std::list<std::unique_ptr<Asteroid>> asteroidManager;
    std::unique_ptr<PowerUp> powerUp;
    sf::Sound shotSound;
    sf::Sound bombSound;
    sf::Sound mainTheme;
    sf::Sound shieldSound;
    sf::Sound gameOver;
    sf::Sound bossBegin;
    sf::Sound bossMiddle;
    sf::Sound bossEnd;
    bool shieldActive = false;
    bool gameEnded = false;
    std::list<Observer *> observers;
    unsigned int destroyedAsteroids;
    unsigned int killedSpaceships;
    unsigned int killedBosses;
    int score;
    float bossAttackTime = 10;
    float finalMovementTime = 0;
    std::list<Cannon *> bossCurrentAttack = {};
    sf::Vector2f finalMovement;
    float enemySpawnGap = 0;
    float asteroidSpawnGap = 0;
    bool bossMode = false;
    bool bossKilled = false;

    static float dist(const sf::Vector2f &pointA, const sf::Vector2f &pointB);

    void
    checkForProjectileCollisions(std::list<std::unique_ptr<Projectile>>::iterator projectileIter, bool isUsingSpecial);

    void checkForAsteroidCollisions(std::list<std::unique_ptr<Asteroid>>::iterator asteroidIter, bool isUsingSpecial);

    void checkForAttractingBeamCollision(std::list<std::unique_ptr<Spaceship>>::iterator enemyIter);

    void checkForLaserCollision(float time);

    void emplaceProjectile(std::unique_ptr<Projectile> projectile);

    void createSounds();


    ///TEST METHODS
public:
    std::list<std::unique_ptr<Projectile>> &getProjectileManagerTest() {
        return projectileManager;
    }

    std::list<std::unique_ptr<Spaceship>> &getEnemyManagerTest() {
        return enemyManager;
    }

    std::list<std::unique_ptr<Asteroid>> &getAsteroidManagerTest() {
        return asteroidManager;
    }


    void emplaceProjectileTest(std::unique_ptr<Projectile> projectile) {
        emplaceProjectile(std::move(projectile));
    }

    void checkForProjectileCollisionsTest(std::list<std::unique_ptr<Projectile>>::iterator projectileIter,
                                          bool isUsingSpecial) {
        checkForProjectileCollisions(projectileIter, isUsingSpecial);
    }

    void checkForAsteroidCollisionsTest(std::list<std::unique_ptr<Asteroid>>::iterator asteroidIter,
                                        bool isUsingSpecial) {
        checkForAsteroidCollisions(asteroidIter, isUsingSpecial);
    }

    void checkForLaserCollisionTest(float time) {
        checkForLaserCollision(time);
    }
};


#endif //ASPACEGAME_ENTITYMANAGER_H
