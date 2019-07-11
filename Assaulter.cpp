//
// Created by gianmarco on 30/06/19.
//

#include <cmath>
#include "Assaulter.h"
#include "ResourceManager.h"
#include "Randomizer.h"

void Assaulter::move(float time) {
    elapsedTime += time;
    boundingBox.setScale(sprite.getScale());
    if (elapsedTime >= assaulterFreezeDuration &&
        elapsedTime - assaulterFreezeDuration < assaulterAppearingDuration) {
        sprite.setScale(
                maxScale - (maxScale * (elapsedTime - assaulterFreezeDuration) / assaulterAppearingDuration),
                maxScale - (maxScale * (elapsedTime - assaulterFreezeDuration) / assaulterAppearingDuration));

    } else if (elapsedTime >= assaulterFreezeDuration + assaulterAppearingDuration &&
               elapsedTime - assaulterFreezeDuration < 2 * assaulterAppearingDuration) {
        if (!moved) {
            setPosition(Randomizer::getRandomPosition(sprite.getOrigin().x * maxScale,
                                                      windowWidth - sprite.getOrigin().x * maxScale,
                                                      assaulterSpawnHeight,
                                                      assaulterSpawnHeight));
            moved = true;
        }
        sprite.setScale(maxScale * ((elapsedTime - assaulterFreezeDuration) / assaulterAppearingDuration - 1),
                        maxScale * ((elapsedTime - assaulterFreezeDuration) / assaulterAppearingDuration - 1));
    } else if (elapsedTime >= assaulterFreezeDuration + 2 * assaulterAppearingDuration) {
        elapsedTime = 0;
        moved = false;
    }
    Enemy::move(0);

}

Assaulter::Assaulter() : Enemy(60.f, 20.f, 0.f, 0.5f, Cannon(Projectile(100, 20.f * 1), 1, 1, true)) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Assaulter.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(Randomizer::getRandomPosition(sprite.getOrigin().x * maxScale,
                                                     windowWidth - sprite.getOrigin().x * maxScale,
                                                     assaulterSpawnHeight, assaulterSpawnHeight));

    boundingBox.setSize(sf::Vector2f(1.5f * sprite.getOrigin().x,
                                     1.5f * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
}

std::unique_ptr<Projectile> Assaulter::useCannon(float dt, Cannon &cannon) {
    return Spaceship::useCannon(dt, cannon);
}

std::unique_ptr<Projectile> Assaulter::useCannon(float dt, Cannon &cannon, const sf::Vector2f &playerPos) {
    if (elapsedTime <= assaulterFreezeDuration) {
        sf::Vector2f vector(playerPos - sprite.getPosition());
        float module = hypot(vector.x, vector.y);
        primaryCannon.getProjectilePrototype().setMovement(sf::Vector2f(vector.x / module, vector.y / module));
        return Spaceship::useCannon(dt, cannon);
    }
    primaryCannon.setElapsedTime(0);
    return Spaceship::useCannon(0, cannon);

}

