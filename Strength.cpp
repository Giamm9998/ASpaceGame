//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "Strength.h"


Strength::Strength() : PowerUp(false) {}

void Strength::powerUp(Player &player) const {
    player.setStrength(player.getStrength() * 1.2f);
    player.getPowerUpSound().play();
}

