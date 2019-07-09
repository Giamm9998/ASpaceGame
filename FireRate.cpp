//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FireRate.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Randomizer.h"

FireRate::FireRate() : PowerUp(false) {}

void FireRate::powerUp(Player *player) {
    player->setFireRate(player->getFireRate() * 10);
}
