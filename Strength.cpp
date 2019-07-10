//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "Strength.h"
#include "ResourceManager.h"
#include "Randomizer.h"
#include "Game.h"


Strength::Strength() : PowerUp(false) {}

void Strength::powerUp(Player &player) const {
    player.setStrength(player.getStrength() * 100); //todo right value
}

