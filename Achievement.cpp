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
    if (scoreBadges < 3)
        checkForScore();
    if (asteroidsBadges < 3)
        checkForAsteroids();
    if (bossesBadges < 3)
        checkForBosses();
    if (spaceshipsBadges < 3)
        checkForSpaceships();
    if (scoreBadges + bossesBadges + spaceshipsBadges + asteroidsBadges == 12)
        detach();
}

void Achievement::checkForScore() {
    if (subject->getScoredPoints() > 1 && scoreBadges == 0) {
        scoreBadges++;
        sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
        appearing = true;
        //implement
    } else if (subject->getScoredPoints() > 1000 && scoreBadges == 1) {
        scoreBadges++;
        sprite.setTextureRect(sf::IntRect(60, 0, 60, 60));
        appearing = true;
        //implement
    } else if (subject->getScoredPoints() > 50000 && scoreBadges == 2) {
        scoreBadges++;
        //implement
    }

}

void Achievement::checkForAsteroids() {
    if (subject->getDestroyedAsteroids() > 10 && asteroidsBadges == 0) {
        asteroidsBadges++;
        //implement
    } else if (subject->getDestroyedAsteroids() > 30 && asteroidsBadges == 1) {
        asteroidsBadges++;
        //implement
    } else if (subject->getDestroyedAsteroids() > 50 && asteroidsBadges == 2) {
        asteroidsBadges++;
        //implement
    }
}

void Achievement::checkForSpaceships() {
    if (subject->getKilledSpaceships() > 10 && spaceshipsBadges == 0) {
        spaceshipsBadges++;
        //implement
    } else if (subject->getKilledSpaceships() > 30 && spaceshipsBadges == 1) {
        spaceshipsBadges++;
        //implement
    } else if (subject->getKilledSpaceships() > 50 && spaceshipsBadges == 2) {
        spaceshipsBadges++;
        //implement
    }
}

void Achievement::checkForBosses() {
    if (subject->getKilledBosses() > 1 && bossesBadges == 0) {
        bossesBadges++;
        //implement
    } else if (subject->getKilledBosses() > 2 && bossesBadges == 1) {
        bossesBadges++;
        //implement
    } else if (subject->getKilledBosses() > 3 && bossesBadges == 2) {
        bossesBadges++;
        //implement
    }
}

sf::Sprite &Achievement::getSprite() {
    return sprite;
}

Achievement::Achievement(EntityManager *subject) : subject(subject),
                                                   asteroidsBadges(0),
                                                   scoreBadges(0),
                                                   spaceshipsBadges(0),
                                                   bossesBadges(0) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/badges.png"));
    appearing = false;
}

bool Achievement::isAppearing() const {
    return appearing;
}

void Achievement::setAppearing(bool appearing) {
    Achievement::appearing = appearing;
}
