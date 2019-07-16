//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FullHealth.h"

FullHealth::FullHealth() : PowerUp(false) {
    sprite.setColor(sf::Color(255, 152, 214));
}

void FullHealth::powerUp(Player &player) const {
    player.setHp(player.getMaxHp());
    player.getPowerUpSound().play();
}
