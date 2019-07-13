//
// Created by gianmarco on 30/06/19.
//

#include <cmath>
#include "Kamikaze.h"
#include "ResourceManager.h"
#include "Functions.h"

void Kamikaze::move(float time) {
    if (!attacking) {
        elapsedTime += time;
        if (elapsedTime >= kamikazeFreezeDuration && elapsedTime - kamikazeFreezeDuration < kamikazeMoveDuration) {
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
        if (elapsedTime == 0) {
            createBeamOutline();
        }
        attract(time);
    }
}

void Kamikaze::createBeamOutline() {
    rect.setSize(sf::Vector2f(3, 0));
    rect.setOrigin(rect.getSize().x / 2, 0);
    rect.setPosition(sprite.getPosition() + sf::Vector2f(0, sprite.getOrigin().y * sprite.getScale().y));
    rect.setFillColor(sf::Color(179, 230, 177));
    rect2 = rect;
}

void Kamikaze::attract(float time) {
    elapsedTime += time;
    if (elapsedTime > 1.5 && elapsedTime <= 2.5) {
        rect.setSize(sf::Vector2f(3, 400 * (elapsedTime - 1.5)));
        rect2.setSize(sf::Vector2f(3, 400 * (elapsedTime - 1.5)));
    } else if (elapsedTime > 3 && elapsedTime <= 4) {
        rect.rotate(10. / (4 - 3) * time);
        rect2.rotate(-10. / (4 - 3) * time);
    } else if (elapsedTime >= 5 && elapsedTime < 10) {
        if (convex.getPointCount() == 0) {
            createBeam();
        }
        if (static_cast<int>((elapsedTime - 5) * 2) % (1 * 2) < 1)
            convex.setFillColor(
                    sf::Color(255, 255, 255, convex.getFillColor().a + static_cast<int>(100. / 0.5 * time)));
        else
            convex.setFillColor(sf::Color(255, 255, 255,
                                          std::max(0, convex.getFillColor().a - static_cast<int>(100. / 0.5 * time))));
    } else if (elapsedTime > 10 && elapsedTime <= 11) {
        convex.setPointCount(0);
        rect.rotate(-10. / (11 - 10) * time);
        rect2.rotate(10. / (11 - 10) * time);
    } else if (elapsedTime > 11 && elapsedTime <= 12) {
        rect.setSize(sf::Vector2f(3, 400 * (12 - elapsedTime)));
        rect2.setSize(sf::Vector2f(3, 400 * (12 - elapsedTime)));
    } else if (elapsedTime > 12) {
        rect.setSize(sf::Vector2f(0, 0));
        rect2.setSize(sf::Vector2f(0, 0));
        attacking = false;
        elapsedTime = 0;
        auto nextPosition = sf::Vector2f(sprite.getPosition().x,
                                         (kamikazeMaxHeight + sprite.getOrigin().y * sprite.getScale().y) / 2);
        sf::Vector2f movementVector(nextPosition - sprite.getPosition());
        float module = hypot(movementVector.x, movementVector.y);
        speed = module / kamikazeMoveDuration;
        movement = sf::Vector2f(movementVector.x / module, movementVector.y / module);
    }
}

void Kamikaze::createBeam() {
    convex.setPointCount(3);
    convex.setPoint(0, sf::Vector2f(rect2.getGlobalBounds().left, rect2.getGlobalBounds().top));
    convex.setPoint(1, sf::Vector2f(rect.getGlobalBounds().left,
                                    rect.getGlobalBounds().top + rect.getGlobalBounds().height));
    convex.setPoint(2, sf::Vector2f(rect2.getGlobalBounds().left + rect2.getGlobalBounds().width,
                                    rect2.getGlobalBounds().top + rect2.getGlobalBounds().height));
    convex.setFillColor(sf::Color(255, 255, 255, 0));
}

void Kamikaze::explode() {}

Kamikaze::Kamikaze() : Enemy(kamikazeHp, kamikazeStregth, kamikazeSpeed, kamikazeFireRate) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Kamikaze.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(static_cast<float>(windowWidth) / 2,
                       (kamikazeMaxHeight + sprite.getOrigin().y * sprite.getScale().y) / 2);

    elapsedTime = kamikazeFreezeDuration;
    boundingBox.setSize(sf::Vector2f(1.5f * sprite.getOrigin().x,
                                     1.5f * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);

    attacking = false;
}

const sf::RectangleShape &Kamikaze::getRect() const {
    return rect;
}

const sf::RectangleShape &Kamikaze::getRect2() const {
    return rect2;
}

const sf::ConvexShape &Kamikaze::getConvex() const {
    return convex;
}
