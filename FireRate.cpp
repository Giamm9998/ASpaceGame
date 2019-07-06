//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FireRate.h"
#include "ResourceManager.h"

FireRate::FireRate() : PowerUp(false) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/BasicProjectile.png")); //TODO add fire rate texture
    sprite.setOrigin(sprite.getLocalBounds().width / 2,
                     sprite.getLocalBounds().height / 2); //TODO add to all the others powerUp
}

void FireRate::powerUp(Player *player) {
    player->getPrimaryCannon().setFireRate(player->getPrimaryCannon().getFireRate() * 1.2);
}
