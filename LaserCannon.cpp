//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "LaserCannon.h"
#include "ResourceManager.h"
#include "Randomizer.h"
#include "Game.h"

LaserCannon::LaserCannon() : PowerUp(true) {}

void LaserCannon::powerUp(Player *player) {
    player->setLaserActive(true);
}
