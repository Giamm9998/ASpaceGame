//
// Created by gianmarco on 12/07/19.
//

#include "Achievement.h"

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
    if (subject->getScoredPoints() > 1000 && scoreBadges == 0) {
        scoreBadges++;
        //implement
    } else if (subject->getScoredPoints() > 10000 && scoreBadges == 1) {
        scoreBadges++;
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
    if (subject->getKilledSpaceships() > 10 && asteroidsBadges == 0) {
        asteroidsBadges++;
        //implement
    } else if (subject->getKilledSpaceships() > 30 && asteroidsBadges == 1) {
        asteroidsBadges++;
        //implement
    } else if (subject->getKilledSpaceships() > 50 && asteroidsBadges == 2) {
        asteroidsBadges++;
        //implement
    }
}

void Achievement::checkForBosses() {
    if (subject->getKilledBosses() > 10 && asteroidsBadges == 0) {
        asteroidsBadges++;
        //implement
    } else if (subject->getKilledBosses() > 30 && asteroidsBadges == 1) {
        asteroidsBadges++;
        //implement
    } else if (subject->getKilledBosses() > 50 && asteroidsBadges == 2) {
        asteroidsBadges++;
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
                                                   bossesBadges(0) {}
