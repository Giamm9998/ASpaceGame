//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FullHealth.h"
#include "ResourceManager.h"

FullHealth::FullHealth() : PowerUp(false) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/FullHealthTexture")); //TODO add full health texture
}

void FullHealth::powerUp(Player *player) {
    player->setHp(player->getMaxHp());
}
