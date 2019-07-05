//
// Created by gianmarco on 30/06/19.
//

#include "Boss.h"
#include "ResourceManager.h"
#include "Randomizer.h"

void Boss::move(float time) {
    elapsedTime += time;
    if (elapsedTime < 5) {
        sprite.move(0, (finalPosition - startPosition) / 5 * time);
    } else
        Enemy::move(time);
    //sprite.rotate(speed*time);
}

void Boss::chooseAttack() {

}

Boss::Boss() : Enemy(1000, 10, 50) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Boss.png"));
    sprite.setScale(0.5, 0.4);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    startPosition = -sprite.getScale().y * sprite.getOrigin().y;
    finalPosition = sprite.getScale().y * sprite.getOrigin().y;

    sprite.setPosition(static_cast<float>(windowWidth) / 2, startPosition);
}
