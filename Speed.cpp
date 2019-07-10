//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "Speed.h"

Speed::Speed() : PowerUp(false) {}

void Speed::powerUp(Player &player) const {
    player.setSpeed(player.getSpeed() * 1.2f);
}
