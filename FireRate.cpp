//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FireRate.h"
#include "ResourceManager.h"

FireRate::FireRate() : PowerUp(false) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BaseProjectile.png")); //TODO add fire rate texture
}

void FireRate::powerUp(Player *player) {
    player->getPrimaryCannon().setFireRate(player->getPrimaryCannon().getFireRate() * 1.2);
}
