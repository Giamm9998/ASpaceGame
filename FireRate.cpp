//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FireRate.h"
#include "ResourceManager.h"

FireRate::FireRate() : PowerUp(false) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BasicProjectile.png")); //TODO add fire rate texture
}

void FireRate::powerUp(Player *player) {
    player->getPrimaryCannon().setFireRate(player->getPrimaryCannon().getFireRate() * 1.2);
}
