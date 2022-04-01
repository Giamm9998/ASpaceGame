//
// Created by gianmarco on 30/06/19.
//

#include <cmath>
#include "Kamikaze.h"
#include "ResourceManager.h"
#include "Functions.h"
#include "Game.h"

Kamikaze::Kamikaze() : Enemy(kamikazeHp, kamikazeStrength, kamikazeSpeed, kamikazeFireRate, Cannon(),
                             kamikazeExplosions) {
    sprite.setTexture(ResourceManager::getTexture("./Texture/Kamikaze.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(windowWidth / 2,
                       (kamikazeMaxHeight + sprite.getOrigin().y * sprite.getScale().y) / 2);

    boundingBox.setSize(sf::Vector2f(1.5f * sprite.getOrigin().x,
                                     1.5f * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);

    for (auto &explosion : explosions) {
        explosion.setScale(explosion.getScale() * 1.5f);
    }

    elapsedTime = -2 * enemySpawnDuration;
    attacking = false;
}

void Kamikaze::move(float time) {
    if (!attacking) {
        elapsedTime += time;
        if (elapsedTime < 0) {
            spawn(time);
            if (elapsedTime > -enemySpawnDuration)
                elapsedTime = kamikazeFreezeDuration;
        } else if (elapsedTime >= kamikazeFreezeDuration &&
                   elapsedTime - kamikazeFreezeDuration < kamikazeMoveDuration) {
            sprite.move(movement * speed * time);
            boundingBox.setPosition(sprite.getPosition());
        } else if (elapsedTime >= kamikazeFreezeDuration + kamikazeMoveDuration) {
            elapsedTime = 0;
            if (sprite.getPosition().y > kamikazeMaxHeight + 20) {
                attacking = true;
                return;
            }

            auto nextPosition = getRandomPosition(sprite.getPosition().x - kamikazeSpanWidth,
                                                  sprite.getPosition().x + kamikazeSpanWidth,
                                                  sprite.getOrigin().y * sprite.getScale().y,
                                                  kamikazeMaxHeight);
            if (getRandomInt(0, 3) == 3)
                nextPosition.y = kamikazeMaxHeight + 100;

            nextPosition.x = std::max(nextPosition.x, sprite.getOrigin().x * sprite.getScale().x);
            nextPosition.x = std::min(nextPosition.x, windowWidth - sprite.getOrigin().x * sprite.getScale().x);

            sf::Vector2f movementVector(nextPosition - sprite.getPosition());
            float module = hypot(movementVector.x, movementVector.y);
            speed = module / kamikazeMoveDuration;
            movement = sf::Vector2f(movementVector.x / module, movementVector.y / module);
        }
    } else {
        if (elapsedTime == 0)
            createBeamOutline();
        attract(time);
    }
}

void Kamikaze::createBeamOutline() {
    beamBorderLeft.setSize(sf::Vector2f(3, 0));
    beamBorderLeft.setOrigin(beamBorderLeft.getSize().x / 2, 0);
    beamBorderLeft.setPosition(sprite.getPosition() + sf::Vector2f(0, sprite.getOrigin().y * sprite.getScale().y));
    beamBorderLeft.setFillColor(sf::Color(179, 230, 177));
    beamBorderRight = beamBorderLeft;
}

void Kamikaze::attract(float time) {
    elapsedTime += time;
    if (!targetAcquired) {
        if (elapsedTime > attractFreezeT && elapsedTime <= beamAppearingT) {
            beamBorderLeft.setSize(sf::Vector2f(3,
                                                400 / (beamAppearingT - attractFreezeT) *
                                                (elapsedTime - attractFreezeT)));
            beamBorderRight.setSize(beamBorderLeft.getSize());
        } else if (elapsedTime > attractFreezeT2 && elapsedTime <= beamRotatingT) {
            beamBorderLeft.rotate(10.f / (beamRotatingT - attractFreezeT2) * time);
            beamBorderRight.rotate(-10.f / (beamRotatingT - attractFreezeT2) * time);
        } else if (elapsedTime >= attractFreezeT3 && elapsedTime < beamAttractingT) {
            acquiringTime = elapsedTime;
            if (beam.getPointCount() == 0)
                createBeam();
            if (static_cast<int>((elapsedTime - attractFreezeT3) * 2) % (1 * 2) < 1)
                beam.setFillColor(
                        sf::Color(255, 255, 255, beam.getFillColor().a + static_cast<sf::Uint8>(100. / 0.5 * time)));
            else
                beam.setFillColor(sf::Color(255, 255, 255,
                                            (sf::Uint8) std::max(0, beam.getFillColor().a -
                                                                    static_cast<int>(100. / 0.5 * time))));
        } else if (elapsedTime > beamAttractingT && elapsedTime <= beamRotatingT2) {
            if (beam.getPointCount() != 0) {
                beam.setPointCount(0);
                beam.setScale(0, 0);
            }
            beamBorderLeft.rotate(-10.f / (beamRotatingT2 - beamAttractingT) * time);
            beamBorderRight.rotate(10.f / (beamRotatingT2 - beamAttractingT) * time);
        } else if (elapsedTime > beamRotatingT2 && elapsedTime <= beamDisappearingT) {
            beamBorderLeft.setSize(sf::Vector2f(3,
                                                400 / (beamDisappearingT - beamRotatingT2) *
                                                (beamDisappearingT - elapsedTime)));
            beamBorderRight.setSize(beamBorderLeft.getSize());
        } else if (elapsedTime > beamDisappearingT) {
            if (!targetAttracted) {
                beamBorderLeft.setSize(sf::Vector2f(0, 0));
                beamBorderRight.setSize(sf::Vector2f(0, 0));
                attacking = false;
                elapsedTime = 0;
                auto nextPosition = sf::Vector2f(sprite.getPosition().x,
                                                 (kamikazeMaxHeight + sprite.getOrigin().y * sprite.getScale().y) / 2);
                sf::Vector2f movementVector(nextPosition - sprite.getPosition());
                float module = hypot(movementVector.x, movementVector.y);
                speed = module / kamikazeMoveDuration;
                movement = sf::Vector2f(movementVector.x / module, movementVector.y / module);
            } else
                hp = 0;
        }
    } else {
        boundingBox.setScale(0, 0);
        if (elapsedTime - acquiringTime <= finalMovementDuration) {
            if (static_cast<int>((elapsedTime) * 4) % (1 * 2) < 1)
                beam.setFillColor(
                        sf::Color(255, 255, 255, beam.getFillColor().a + static_cast<sf::Uint8>(100. / 0.25 * time)));
            else
                beam.setFillColor(sf::Color(255, 255, 255, (sf::Uint8) std::max(0, beam.getFillColor().a -
                                                                                   static_cast<int>(100. / 0.25 *
                                                                                                    time))));

        } else if (elapsedTime - acquiringTime - finalMovementDuration >= 0.5) {
            targetAcquired = false;
            targetAttracted = true;
            elapsedTime = beamAttractingT;
        }
    }
}

void Kamikaze::createBeam() {
    beam.setPointCount(3);
    beam.setScale(1, 1);
    beam.setPoint(0, sf::Vector2f(beamBorderRight.getGlobalBounds().left, beamBorderRight.getGlobalBounds().top));
    beam.setPoint(1, sf::Vector2f(beamBorderLeft.getGlobalBounds().left,
                                  beamBorderLeft.getGlobalBounds().top + beamBorderLeft.getGlobalBounds().height));
    beam.setPoint(2, sf::Vector2f(beamBorderRight.getGlobalBounds().left + beamBorderRight.getGlobalBounds().width,
                                  beamBorderRight.getGlobalBounds().top + beamBorderRight.getGlobalBounds().height));
    beam.setFillColor(sf::Color(255, 255, 255, 0));
}

const sf::RectangleShape &Kamikaze::getBeamBorderLeft() const {
    return beamBorderLeft;
}

const sf::RectangleShape &Kamikaze::getBeamBorderRight() const {
    return beamBorderRight;
}

const sf::ConvexShape &Kamikaze::getBeam() const {
    return beam;
}

bool Kamikaze::isAttacking() const {
    return attacking;
}

void Kamikaze::setTargetAcquired(bool acquired) {
    Kamikaze::targetAcquired = acquired;
}
