//
// Created by gianmarco on 30/06/19.
//

#include <cmath>
#include "Assaulter.h"
#include "ResourceManager.h"
#include "Spaceship.h"
#include "Randomizer.h"
#include "Game.h"

void Assaulter::move(float time) {
    elapsedTime += time;
    boundingBox.setScale(sprite.getScale());
    if (elapsedTime >= ASSAULTER_FREEZE_DURATION &&
        elapsedTime - ASSAULTER_FREEZE_DURATION < ASSAULTER_APPEARING_DURATION) {
        sprite.setScale(
                maxScale - (maxScale * (elapsedTime - ASSAULTER_FREEZE_DURATION) / ASSAULTER_APPEARING_DURATION),
                maxScale - (maxScale * (elapsedTime - ASSAULTER_FREEZE_DURATION) / ASSAULTER_APPEARING_DURATION));

    } else if (elapsedTime >= ASSAULTER_FREEZE_DURATION + ASSAULTER_APPEARING_DURATION &&
               elapsedTime - ASSAULTER_FREEZE_DURATION < 2 * ASSAULTER_APPEARING_DURATION) {
        if (!moved) {
            setPosition(Randomizer::getRandomPosition(sprite.getOrigin().x * maxScale,
                                                      windowWidth - sprite.getOrigin().x * maxScale,
                                                      assaulterSpawnHeight,
                                                      assaulterSpawnHeight)); //todo not based on constants
            moved = true;
        }
        sprite.setScale(maxScale * ((elapsedTime - ASSAULTER_FREEZE_DURATION) / ASSAULTER_APPEARING_DURATION - 1),
                        maxScale * ((elapsedTime - ASSAULTER_FREEZE_DURATION) / ASSAULTER_APPEARING_DURATION - 1));
    } else if (elapsedTime >= ASSAULTER_FREEZE_DURATION + 2 * ASSAULTER_APPEARING_DURATION) {
        elapsedTime = 0;
        moved = false;
    }
    Enemy::move(0);

}

Assaulter::Assaulter() : Enemy(60.f, 20.f, 0.f, 0.5f) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Assaulter.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(Randomizer::getRandomPosition(sprite.getOrigin().x * maxScale,
                                                     windowWidth - sprite.getOrigin().x * maxScale,
                                                     assaulterSpawnHeight, assaulterSpawnHeight));
    primaryCannon.setTracker(true);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(100, strength * primaryCannon.getStrengthMultiplier());
    primaryCannon.setProjectilePrototype(projectilePrototype);

    boundingBox.setSize(sf::Vector2f(1.5 * sprite.getOrigin().x,
                                     1.5 * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);

    //TODO establish the right default values
}

std::unique_ptr<Projectile> Assaulter::useCannon(float dt, Cannon &cannon) {
    return Spaceship::useCannon(dt, cannon);
}

std::unique_ptr<Projectile> Assaulter::useCannon(float dt, Cannon &cannon, sf::Vector2f playerPos) {
    if (elapsedTime <= ASSAULTER_FREEZE_DURATION) {
        sf::Vector2f vector(playerPos - sprite.getPosition());
        float module = hypot(vector.x, vector.y);
        primaryCannon.getProjectilePrototype().setMovement(sf::Vector2f(vector.x / module, vector.y / module));
        return Spaceship::useCannon(dt, cannon);
    }
    primaryCannon.setElapsedtime(0);
    return Spaceship::useCannon(0, cannon);

}

