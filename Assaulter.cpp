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
    if (elapsedTime >= 4 && elapsedTime < 4.5 && !moved) {
        if (currentScale <= 0.01) {
            sprite.setScale(0, 0);
            setPosition(Randomizer::getRandomPosition(50, windowWidth - 50, 50, 50));
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

}

Assaulter::Assaulter() : Enemy(50, 20, 30) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Assaulter.png"));
    sprite.setPosition(Randomizer::getRandomPosition(50, windowWidth - 50, 50, 50));
    sprite.setOrigin(109, 128);
    primaryCannon.setFireRate(0.5);
    primaryCannon.setTracker(true);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 100, sf::Vector2f(0, 1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);
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

