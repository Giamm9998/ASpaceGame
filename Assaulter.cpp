//
// Created by gianmarco on 30/06/19.
//

#include "Assaulter.h"
#include "ResourceManager.h"

void Assaulter::move() {
    Enemy::move();
}

Assaulter::Assaulter() : Enemy(50, 20, 30) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Assaulter.png"))
}
