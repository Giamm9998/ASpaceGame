//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_KAMIKAZE_H
#define ASPACEGAME_KAMIKAZE_H

static const float kamikazeFreezeDuration = 2;
static const float kamikazeMoveDuration = 0.2;
static const float kamikazeMaxHeight = 120;
static const float kamikazeSpanWidth = 150;
static const float kamikazeHp = 150;
static const float kamikazeStrength = 30;
static const float kamikazeSpeed = 70;
static const float kamikazeFireRate = 0.8;

static const float attractFreezeT = 1.5;
static const float beamAppearingT = attractFreezeT + 1;
static const float attractFreezeT2 = beamAppearingT + 0.5f;
static const float beamRotatingT = attractFreezeT2 + 1;
static const float attractFreezeT3 = beamRotatingT + 1;
static const float beamAttractingT = attractFreezeT3 + 5;
static const float beamRotatingT2 = beamAttractingT + 1;
static const float beamDisappearingT = 12;
static const int kamikazeExplosions = 10;

#include "Enemy.h"

class Kamikaze: public Enemy {
public:
    Kamikaze();

    void move(float time) override;

    void attract(float time);

    const sf::RectangleShape &getBeamBorderLeft() const;

    const sf::RectangleShape &getBeamBorderRight() const;

    const sf::ConvexShape &getBeam() const;

    bool isAttacking() const;

    void setTargetAcquired(bool acquired);

private:
    sf::Vector2f movement;
    sf::RectangleShape beamBorderLeft;
    sf::RectangleShape beamBorderRight;
    sf::ConvexShape beam;
    bool attacking;
    bool targetAcquired = false;
    bool targetAttracted = false;
    float acquiringTime = 0;

    void createBeamOutline();

    void createBeam();
};


#endif //ASPACEGAME_KAMIKAZE_H
