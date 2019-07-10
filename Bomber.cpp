//
// Created by gianmarco on 30/06/19.
//
#include <math.h>
#include "Bomber.h"
#include "ResourceManager.h"

Bomber::Bomber() : Player(200.f, 15.f, 120.f, 1.2f) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BomberBasic.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(400, strength * primaryCannon.getStrengthMultiplier(), false);
    primaryCannon.setElapsedtime(1.f / (fireRate * primaryCannon.getFireRateMultiplier()));
    primaryCannon.setProjectilePrototype(projectilePrototype);

    laser.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height / 2);

    secondaryCannon.setSpaceshipPtr(this);
    secondaryCannon.setFireRateMultiplier(0.5);
    secondaryCannon.setStrengthMultiplier(3);
    Projectile secondaryProjectilePrototype(200, strength * secondaryCannon.getStrengthMultiplier(),
                                            false, sf::Vector2f(0.9, 0.9));
    secondaryCannon.setProjectilePrototype(secondaryProjectilePrototype);

    boundingBox.setSize(sf::Vector2f(1.2 * sprite.getOrigin().x,
                                     1.3 * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y + sprite.getGlobalBounds().height / 16);
    //TODO establish the right default values for both cannons
}


Cannon &Bomber::getSecondaryCannon() {
    return secondaryCannon;
}

std::unique_ptr<Projectile> Bomber::useBomb(sf::RectangleShape &specialHud) {
    float dt = 1.f / (fireRate * secondaryCannon.getFireRateMultiplier());
    charging = true;
    elapsedTime = 0;
    specialHud.setScale(1, 0);
    return useCannon(dt, secondaryCannon);
}

void Bomber::recharge(float dt, sf::RectangleShape &specialHud) {
    elapsedTime += dt;
    specialHud.setScale(1, std::min(1., elapsedTime * fireRate * secondaryCannon.getFireRateMultiplier()));
    if (elapsedTime > 1.f / (fireRate * secondaryCannon.getFireRateMultiplier())) {
        elapsedTime = 0;
        charging = false;
    }
}