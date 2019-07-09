//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FullHealth.h"
#include "ResourceManager.h"

FullHealth::FullHealth() : PowerUp(false) {}

void FullHealth::powerUp(Player &player) {
    player.setHp(player.getMaxHp());
}
