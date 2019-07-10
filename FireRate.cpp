//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FireRate.h"

FireRate::FireRate() : PowerUp(false) {
    sprite.setColor(sf::Color::Magenta);
}

void FireRate::powerUp(Player &player) const {
    player.setFireRate(player.getFireRate() * 10); //todo right value
}