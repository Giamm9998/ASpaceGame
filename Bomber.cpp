//
// Created by gianmarco on 30/06/19.
//
#include "Bomber.h"
#include "ResourceManager.h"

Bomber::Bomber() : Player(150.f, 10.f, 120.f, 1.f, 150.f) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BomberBasic.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    primaryCannon.setTracker(false);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 400, sf::Vector2f(0, -1),
                                   strength * primaryCannon.getStrengthMultiplier(), false);
    primaryCannon.setProjectilePrototype(projectilePrototype);
    laser.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height / 2);
    secondaryCannon.setSpaceshipPtr(this);
    secondaryCannon.setFireRateMultiplier(0.5);
    Projectile secondaryProjectilePrototype(sf::Vector2f(0.9, 0.9), 200, sf::Vector2f(0, -1),
                                            strength * secondaryCannon.getStrengthMultiplier(), false);
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

std::unique_ptr<Projectile> Bomber::useBomb(float dt, sf::RectangleShape &specialHud) {
    elapsedTime += dt;
    std::unique_ptr<Projectile> shot = useCannon(dt, &secondaryCannon);
    if (shot != nullptr) {
        charging = true;
        elapsedTime = 0;
    } else specialHud.setScale(1, 1 - elapsedTime / (1.f / (fireRate * secondaryCannon.getFireRateMultiplier())));

    return shot;
}

void Bomber::recharge(float dt, sf::RectangleShape &specialHud) {
    elapsedTime += dt;
    specialHud.setScale(1, elapsedTime / (1.f / (fireRate * secondaryCannon.getFireRateMultiplier())));
    if (elapsedTime > 1.f / (fireRate * secondaryCannon.getFireRateMultiplier())) {
        elapsedTime = 0;
        charging = false;
    }
}