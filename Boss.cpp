//
// Created by gianmarco on 30/06/19.
//

#include "Boss.h"
#include "ResourceManager.h"

void Boss::move(float time) {
    sprite.rotate(speed * time);
}

void Boss::chooseAttack() {

}

Boss::Boss() : Enemy(1000, 10, 10) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Boss.png"));
}
