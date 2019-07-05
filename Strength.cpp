//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "Strength.h"
#include "ResourceManager.h"


Strength::Strength() : PowerUp(false) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/StrengthTexture")); //TODO add strength texture
}

void Strength::powerUp(Player *player) {
    player->setStrength(player->getStrength() * 1.2);
}

