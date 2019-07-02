//
// Created by Fabio Luccioletti on 2019-07-02.
//

#include "Minion.h"
#include "ResourceManager.h"

Minion::Minion() : Enemy(50, 10, 100), elapsedTime(0) { //todo cambia
    sprite.setTexture(ResourceManager::getTexture("../Texture/Minion.png"));
}

void Minion::move(float time) {
    elapsedTime += time;
    if (elapsedTime < 1)
        sprite.move(speed * time, 0);
    else if (elapsedTime > 2)
        elapsedTime = 0;
}
