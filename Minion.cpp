//
// Created by Fabio Luccioletti on 2019-07-02.
//

#include "Minion.h"
#include "ResourceManager.h"

Minion::Minion() : Enemy(50, 10, 10) { //todo cambia
    sprite.setTexture(ResourceManager::getTexture("../Texture/Minion.png"));
}

void Minion::move(float time) {
    Enemy::move(time);
}
