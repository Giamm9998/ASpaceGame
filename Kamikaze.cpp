//
// Created by gianmarco on 30/06/19.
//

#include <cmath>
#include "Kamikaze.h"
#include "ResourceManager.h"
#include "Functions.h"

void Kamikaze::move(float time) {
    elapsedTime += time;
    if (elapsedTime >= kamikazeFreezeDuration && elapsedTime - kamikazeFreezeDuration < kamikazeMoveDuration) {
        sprite.move(movement * speed * time);
        boundingBox.setPosition(sprite.getPosition());
    } else if (elapsedTime >= kamikazeFreezeDuration + kamikazeMoveDuration) {
        elapsedTime = 0;
        auto nextPosition = getRandomPosition(sprite.getPosition().x - kamikazeSpanWidth,
                                              sprite.getPosition().x + kamikazeSpanWidth,
                                                          sprite.getOrigin().y * sprite.getScale().y,
                                              kamikazeMaxHeight);

        nextPosition.x = std::max(nextPosition.x, sprite.getOrigin().x * sprite.getScale().x);
        nextPosition.x = std::min(nextPosition.x, windowWidth - sprite.getOrigin().x * sprite.getScale().x);

        sf::Vector2f movementVector(nextPosition - sprite.getPosition());
        float module = hypot(movementVector.x, movementVector.y);
        speed = module / kamikazeMoveDuration;
        movement = sf::Vector2f(movementVector.x / module, movementVector.y / module);
    }
}

void Kamikaze::attract() {}

void Kamikaze::explode() {}

Kamikaze::Kamikaze() : Enemy(kamikazeHp, kamikazeStregth, kamikazeSpeed, kamikazeFireRate,
                             Cannon(Projectile(kamikazeProjectileSpeed, kamikazeStregth * 1))) {
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
}
