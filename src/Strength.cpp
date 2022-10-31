//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "Strength.h"


Strength::Strength() : PowerUp(false) {
    sprite.setColor(sf::Color::Yellow);
}

void Strength::powerUp(Player &player) const {
    player.setStrength(player.getStrength() + 2.5f);
    player.getPowerUpSound().play();
}

