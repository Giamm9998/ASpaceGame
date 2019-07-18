//
// Created by gianmarco on 12/07/19.
//

#include "Achievement.h"
#include "ResourceManager.h"

void Achievement::attach() {
    subject->subscribe(this);
}

void Achievement::detach() {
    subject->unsubscribe(this);
}

void Achievement::update() {
    if (scoreBadges < 4)
        checkForScore();
    if (asteroidsBadges < 4)
        checkForAsteroids();
    if (bossesBadges < 4)
        checkForBosses();
    if (spaceshipsBadges < 4)
        checkForSpaceships();
    if (scoreBadges + bossesBadges + spaceshipsBadges + asteroidsBadges == 16)
        detach();
}

void Achievement::checkForScore() {
    if (subject->getScore() >= 3000 && scoreBadges == 0) {
        scoreBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/ScoreAchievement1.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getScore() >= 8000 && scoreBadges == 1) {
        scoreBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/ScoreAchievement2.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getScore() >= 15000 && scoreBadges == 2) {
        scoreBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/ScoreAchievement3.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getScore() >= 25000 && scoreBadges == 3) {
        scoreBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/ScoreAchievement4.png"));
        sprites.emplace_back(sprite);
    }

}

void Achievement::checkForAsteroids() {
    if (subject->getDestroyedAsteroids() >= 10 && asteroidsBadges == 0) {
        asteroidsBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/AsteroidAchievement1.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getDestroyedAsteroids() >= 25 && asteroidsBadges == 1) {
        asteroidsBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/AsteroidAchievement2.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getDestroyedAsteroids() >= 50 && asteroidsBadges == 2) {
        asteroidsBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/AsteroidAchievement3.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getDestroyedAsteroids() >= 150 && asteroidsBadges == 3) {
        asteroidsBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/AsteroidAchievement4.png"));
        sprites.emplace_back(sprite);
    }
}


void Achievement::checkForSpaceships() {
    if (subject->getKilledSpaceships() >= 20 && spaceshipsBadges == 0) {
        spaceshipsBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/EnemyAchievement1.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getKilledSpaceships() >= 50 && spaceshipsBadges == 1) {
        spaceshipsBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/EnemyAchievement2.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getKilledSpaceships() >= 100 && spaceshipsBadges == 2) {
        spaceshipsBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/EnemyAchievement3.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getKilledSpaceships() >= 200 && spaceshipsBadges == 3) {
        spaceshipsBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/EnemyAchievement4.png"));
        sprites.emplace_back(sprite);
    }
}

void Achievement::checkForBosses() {
    if (subject->getKilledBosses() >= 1 && bossesBadges == 0) {
        bossesBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/BossAchievement1.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getKilledBosses() >= 2 && bossesBadges == 1) {
        bossesBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/BossAchievement2.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getKilledBosses() >= 3 && bossesBadges == 2) {
        bossesBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/BossAchievement3.png"));
        sprites.emplace_back(sprite);
    }
    if (subject->getKilledBosses() >= 4 && bossesBadges == 3) {
        bossesBadges++;
        sprite.setTexture(ResourceManager::getTexture("../Texture/BossAchievement4.png"));
        sprites.emplace_back(sprite);
    }
}

std::list<sf::Sprite> &Achievement::getSprites() {
    return sprites;
}

Achievement::Achievement(EntityManager *subject) : subject(subject),
                                                   asteroidsBadges(0),
                                                   scoreBadges(0),
                                                   spaceshipsBadges(0),
                                                   bossesBadges(0) {
}