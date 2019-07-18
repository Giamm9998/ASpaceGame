//
// Created by gianmarco on 30/06/19.
//

#include "Fighter.h"
#include "ResourceManager.h"
#include "Functions.h"
#include "Game.h"

void Fighter::move(float time) {
    elapsedTime += time;
    if (elapsedTime < 0)
        spawn(time);
    else
        Enemy::move(time);
}

Fighter::Fighter() : Enemy(fighterHp, fighterStrength, fighterSpeed, fighterFireRate, Cannon(Projectile(
        fighterProjectileSpeed, fighterStrength * 1)), fighterExplosions) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Fighter.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(getRandomPosition(sprite.getOrigin().x * maxScale,
                                         windowWidth - sprite.getOrigin().x * maxScale,
                                         fighterSpawnHeight, fighterSpawnHeight));

    externalCannons.emplace_back(Cannon(primaryCannon.getProjectilePrototype(), 1, 1, false,
                                        sf::Vector2f(-fighterCannonRelativePosition, 0)));
    externalCannons.emplace_back(Cannon(primaryCannon.getProjectilePrototype(), 1, 1, false,
                                        sf::Vector2f(fighterCannonRelativePosition, 0)));

    boundingBox.setSize(sf::Vector2f(fighterBoxSizeX * sprite.getOrigin().x,
                                     fighterBoxSizeY * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
}

std::vector<Cannon> &Fighter::getExternalCannons() {
    return externalCannons;
}
