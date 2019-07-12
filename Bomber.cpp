//
// Created by gianmarco on 30/06/19.
//
#include <cmath>
#include "Bomber.h"
#include "ResourceManager.h"

Bomber::Bomber() : Player(bomberHp, bomberStrength, bomberSpeed, bomberFireRate,
                          Cannon(Projectile(bomberProjectileSpeed, bomberStrength * 1, false))),
                   secondaryCannon(Projectile(bombSpeed, bomberStrength * bomberSecondaryStrengthMult,
                                              false, sf::Vector2f(bombSize, bombSize)), bomberSecondaryFireRateMult,
                                   bomberSecondaryStrengthMult, false) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BomberBasic.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    primaryCannon.setElapsedTime(1.f / (fireRate * primaryCannon.getFireRateMultiplier()));

    laser.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height / 2);

    boundingBox.setSize(sf::Vector2f(1.2f * sprite.getOrigin().x,
                                     1.3f * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y + sprite.getGlobalBounds().height / 16);
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
    specialHud.setScale(1, std::min(1.f, elapsedTime * fireRate * secondaryCannon.getFireRateMultiplier()));
    if (elapsedTime > 1.f / (fireRate * secondaryCannon.getFireRateMultiplier())) {
        elapsedTime = 0;
        charging = false;
    }
}