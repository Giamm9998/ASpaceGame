//
// Created by gianmarco on 30/06/19.
//

#include "Fighter.h"
#include "ResourceManager.h"

void Fighter::move() {
    Enemy::move();
}

Fighter::Fighter() : Enemy(50, 10, 30) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Fighter.png"));
}
