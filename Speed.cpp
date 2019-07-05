//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "Speed.h"
#include "ResourceManager.h"

Speed::Speed() : PowerUp(false) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/SpeedTexture")); //TODO add speed texture
}

void Speed::powerUp(Player *player) {
    player->setSpeed(player->getSpeed() * 1.2);
}
