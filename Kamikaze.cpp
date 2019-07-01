//
// Created by gianmarco on 30/06/19.
//

#include "Kamikaze.h"
#include "ResourceManager.h"

void Kamikaze::move() {
    Enemy::move();
}

void Kamikaze::attract() {}

void Kamikaze::explode() {}

Kamikaze::Kamikaze() : Enemy(50, 30, 30) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Kamikaze.png"));
}
