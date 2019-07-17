//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FireRate.h"

FireRate::FireRate() : PowerUp(false) {
    sprite.setColor(sf::Color(132, 70, 240));
}

void FireRate::powerUp(Player &player) const {
    player.getPrimaryCannon().setFireRateMultiplier(player.getPrimaryCannon().getFireRateMultiplier() * 1.2f);
    for (auto &cannon : player.getAuxiliaryCannons())
        cannon.setFireRateMultiplier(cannon.getFireRateMultiplier() * 1.2f);
    player.getPowerUpSound().play();
}