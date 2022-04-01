//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "Health.h"

Health::Health() : PowerUp(false) {
    sprite.setColor(sf::Color(255, 152, 214));
}

void Health::powerUp(Player &player) const {
    player.setHp(std::min(player.getMaxHp(), player.getHp() + 0.33f * player.getMaxHp()));
    player.getPowerUpSound().play();
}
