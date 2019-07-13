//
// Created by gianmarco on 30/06/19.
//

#include "Boss.h"
#include "ResourceManager.h"

void Boss::move(float time) {
    elapsedTime += time;
    if (elapsedTime < bossSpawnDuration) {
        sprite.move(0, (bossFinalPosition - bossStartPosition) / bossSpawnDuration * time);
        //boundingBox.setScale(0,0); //todo invincible during spawn
    } else
        Enemy::move(time);
}

void Boss::chooseAttack() {

}

Boss::Boss() : Enemy(1000.f, 10.f, 50.f, 1.f, Cannon(), 15) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Boss.png"));
    sprite.setScale(0.5, 0.4);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    bossStartPosition = -sprite.getScale().y * sprite.getOrigin().y;
    bossFinalPosition = sprite.getScale().y * sprite.getOrigin().y + bossSpawnHeight;

    sprite.setPosition(static_cast<float>(windowWidth) / 2, bossStartPosition);

    boundingBox.setSize(sf::Vector2f(1.6f * sprite.getOrigin().x,
                                     1.4f * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
}
