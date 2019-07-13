//
// Created by Fabio Luccioletti on 2019-07-10.
//

#ifndef ASPACEGAME_ENTITYMANAGER_H
#define ASPACEGAME_ENTITYMANAGER_H


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

    void updateEnemies(float time, int &score);

    void updatePlayer(float time, bool isMovingRight, bool isMovingLeft, bool isShooting, bool isUsingSpecial,
                      sf::RectangleShape &specialHud, sf::RectangleShape &hpHud);

    void updateProjectiles(float time, bool isUsingSpecial);

    void updatePowerUp(float time);

    void updateAsteroids(float time, int &score, bool isUsingSpecial);

    static bool isOutOfSigth(const sf::Sprite &sprite);

    void subscribe(Observer *o) override;

    void unsubscribe(Observer *o) override;

    void notify() override;

    unsigned int getDestroyedAsteroids() const;

    unsigned int getKilledSpaceships() const;

    unsigned int getKilledBosses() const;

    unsigned int getScoredPoints() const;

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
    bool shieldActive = false;
    std::list<Observer *> observers;
    unsigned int destroyedAsteroids;
    unsigned int killedSpaceships;
    unsigned int killedBosses;
    unsigned int scoredPoints;
    float bossAttacktime = 10;
    std::list<Cannon *> bossCurrentAttack = {};

    static float dist(const sf::Vector2f &pointA, const sf::Vector2f &pointB);

    void
    checkForProjectileCollisions(std::list<std::unique_ptr<Projectile>>::iterator projectileIter, bool isUsingSpecial);

    void checkForAsteroidsCollisions(std::list<std::unique_ptr<Asteroid>>::iterator asteroidIter, bool isUsingSpecial);

    void checkForLaserCollision(float time);

    void emplaceProjectile(std::unique_ptr<Projectile> projectile);

    void createSounds();


};


#endif //ASPACEGAME_ENTITYMANAGER_H
