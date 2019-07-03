//
// Created by gianmarco on 30/06/19.
//

#include "Assaulter.h"
#include "ResourceManager.h"
#include "Spaceship.h"
#include "Randomizer.h"
#include "Game.h"

void Assaulter::move(float time) {
    elapsedTime += time;
    auto currentScale = sprite.getScale().x;
    if (elapsedTime >= 4 && elapsedTime < 6 && currentScale >= 0.01) {
        sprite.setScale(currentScale - (escapeSpeed * time),
                        currentScale - (escapeSpeed * time));
    } else if (elapsedTime >= 6 && currentScale <= maxScale) {
        if (!moved) {
            setPosition(Randomizer::getRandomPosition(50, windowWidth - 50, 50, 50));
            moved = true;
        }
        sprite.setScale(currentScale + (escapeSpeed * time), currentScale + (escapeSpeed * time));
    } else if (elapsedTime >= 8) {
        elapsedTime = 0;
        moved = false;
    }

}

Assaulter::Assaulter() : Enemy(50, 20, 30), elapsedTime(0) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Assaulter.png"));
    sprite.rotate(180);
    sprite.setPosition(Randomizer::getRandomPosition(50, windowWidth - 50, 50, 50));
    sprite.setOrigin(109, 128);
    primaryCannon.setFireRate(100);
    primaryCannon.setNShots(1);
    primaryCannon.setTracker(true);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 40, &primaryCannon, sf::Vector2f(0, 1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    //TODO establish the right default values
}
