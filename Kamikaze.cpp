//
// Created by gianmarco on 30/06/19.
//

#include <cmath>
#include "Kamikaze.h"
#include "ResourceManager.h"
#include "Randomizer.h"

void Kamikaze::move(float time) {
    elapsedTime += time;
    if (elapsedTime >= kamikazeFreezeDuration && elapsedTime - kamikazeFreezeDuration < kamikazeMoveDuration) {
        sprite.move(movement * speed * time);
        Enemy::move(0);
    } else if (elapsedTime >= kamikazeFreezeDuration + kamikazeMoveDuration) {
        elapsedTime = 0;
        auto nextPosition = Randomizer::getRandomPosition(sprite.getPosition().x - kamikazeSpawnWidth,
                                                          sprite.getPosition().x + kamikazeSpawnWidth,
                                                          sprite.getOrigin().y * sprite.getScale().y,
                                                          kamikazeMaxSpawnHeight);

        nextPosition.x = std::max(nextPosition.x, sprite.getOrigin().x * sprite.getScale().x);
        nextPosition.x = std::min(nextPosition.x, windowWidth - sprite.getOrigin().x * sprite.getScale().x);

        sf::Vector2f vector(nextPosition - sprite.getPosition());
        float module = hypot(vector.x, vector.y);
        speed = module / kamikazeMoveDuration;
        movement = sf::Vector2f(vector.x / module, vector.y / module);
    }
}

void Kamikaze::attract() {}

void Kamikaze::explode() {}

Kamikaze::Kamikaze() : Enemy(60.f, 30.f, 70.f, 0.8f, Cannon(Projectile(200, 30.f * 1))) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Kamikaze.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    sprite.setPosition(static_cast<float>(windowWidth) / 2,
                       (kamikazeMaxSpawnHeight + sprite.getOrigin().y * sprite.getScale().y) / 2);
    boundingBox.setSize(sf::Vector2f(1.5f * sprite.getOrigin().x,
                                     1.5f * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
}
