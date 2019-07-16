//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "Speed.h"

Speed::Speed() : PowerUp(false) {
    sprite.setColor(sf::Color::Cyan);
}

void Speed::powerUp(Player &player) const {
    player.setSpeed(player.getSpeed() * 1.2f);
    player.getPowerUpSound().play();
}
