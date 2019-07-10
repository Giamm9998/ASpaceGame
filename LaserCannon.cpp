//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "LaserCannon.h"

LaserCannon::LaserCannon() : PowerUp(true) {
    sprite.setColor(sf::Color::Red);
}

void LaserCannon::powerUp(Player &player) const {
    player.setLaserActive(true);
}
