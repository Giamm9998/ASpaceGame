//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FireRate.h"

FireRate::FireRate() : PowerUp(false) {
    sprite.setColor(sf::Color(216, 143, 255));
}

void FireRate::powerUp(Player &player) const {
    player.setFireRate(player.getFireRate() * 1.2f);
    player.getPowerUpSound().play();
}