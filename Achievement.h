//
// Created by gianmarco on 12/07/19.
//

#ifndef ASPACEGAME_ACHIEVEMENT_H
#define ASPACEGAME_ACHIEVEMENT_H


#include "Observer.h"
#include "EntityManager.h"

class Achievement : public Observer {
public:
    void attach() override;

    void detach() override;

    void update() override;

    sf::Sprite &getSprite();

    explicit Achievement(EntityManager *subject);

    bool isAppearing() const;

    void setAppearing(bool appearing);

private:
    EntityManager *subject;
    unsigned int asteroidsBadges;
    unsigned int scoreBadges;
    unsigned int spaceshipsBadges;
    unsigned int bossesBadges;
    bool appearing;
    sf::Sound achievementSound;

    void checkForAsteroids();

    void checkForSpaceships();

    void checkForBosses();

    void checkForScore();

    sf::Sprite sprite;
};


#endif //ASPACEGAME_ACHIEVEMENT_H
