//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FireRate.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Randomizer.h"

FireRate::FireRate() : PowerUp(false) {
    sprite.setColor(sf::Color::Magenta);
}

void FireRate::powerUp(Player &player) const {
    player.setFireRate(player.getFireRate() * 10);
}
