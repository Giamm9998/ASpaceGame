//
// Created by gianmarco on 30/06/19.
//

#include "Boss.h"
#include "ResourceManager.h"

void Boss::move(float time) {
    sprite.rotate(10 * speed * time);
}

void Boss::chooseAttack() {

}

Boss::Boss() : Enemy(1000, 10, 10) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Boss.png"));
    sprite.setOrigin(338, 254);

}
