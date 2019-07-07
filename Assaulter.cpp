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
    auto currentScale = sprite.getScale().x;
    boundingBox.setScale(sprite.getScale());
    if (elapsedTime >= 4 && elapsedTime < 4.5 && !moved) {
        if (currentScale <= 0.01) {
            sprite.setScale(0, 0);
            setPosition(Randomizer::getRandomPosition(
                    sprite.getOrigin().x * maxScale,
                    windowWidth - sprite.getOrigin().x * maxScale, 50, 50)); //todo not based on constants
            moved = true;
        } else {
            sprite.setScale(currentScale - (escapeSpeed * time),
                            currentScale - (escapeSpeed * time));
        }

    } else if (elapsedTime >= 4.5 && currentScale <= maxScale) {
        sprite.setScale(currentScale + (escapeSpeed * time), currentScale + (escapeSpeed * time));
    } else if (elapsedTime >= 6) {
        elapsedTime = 0;
        moved = false;
    }
    Enemy::move(0);

}

Assaulter::Assaulter() : Enemy(50, 20, 0) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Assaulter.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(Randomizer::getRandomPosition(sprite.getOrigin().x * maxScale,
                                                     windowWidth - sprite.getOrigin().x * maxScale, 50,
                                                     50)); //todo not based on constants
    primaryCannon.setFireRate(0.5);
    primaryCannon.setTracker(true);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 100, sf::Vector2f(0, 1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);

    boundingBox.setSize(sf::Vector2f(1.5 * sprite.getOrigin().x,
                                     1.5 * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);

    //TODO establish the right default values
}

std::unique_ptr<Projectile> Assaulter::useCannon(float dt, Cannon *cannon) {
    return Spaceship::useCannon(dt, cannon);
}

std::unique_ptr<Projectile> Assaulter::useCannon(float dt, Cannon *cannon, sf::Vector2f playerPos) {
    if (elapsedTime <= 4) {
        sf::Vector2f vector;
        vector.x = playerPos.x - sprite.getPosition().x;
        vector.y = playerPos.y - sprite.getPosition().y;
        float module = hypot(vector.x, vector.y);
        primaryCannon.getProjectilePrototype().setMovement(sf::Vector2f(vector.x / module, vector.y / module));
        return Spaceship::useCannon(dt, cannon);
    }
    primaryCannon.setElapsedtime(0);
    return Spaceship::useCannon(0, cannon);

}

