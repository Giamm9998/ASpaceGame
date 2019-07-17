//
// Created by Fabio Luccioletti on 2019-07-02.
//

#include "Minion.h"
#include "ResourceManager.h"
#include "Functions.h"

Minion::Minion() : Enemy(75.f, 15.f, 100.f, 0.5f, Cannon(Projectile(250, 15.f * 1))) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Minion.png"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(getRandomPosition(sprite.getOrigin().x * maxScale,
                                                     windowWidth - sprite.getOrigin().x * maxScale,
                                         minionSpawnHeight, minionSpawnHeight));

    boundingBox.setSize(sf::Vector2f(1.5f * sprite.getOrigin().x,
                                     1.5f * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
}

void Minion::move(float time) {
    elapsedTime += time;
    if (elapsedTime < 0)
        spawn(time);
    else if (elapsedTime <= minionFreezeDuration) {
        Enemy::move(time);
    } else if (elapsedTime > 2 * minionFreezeDuration)
        elapsedTime = 0;
}
