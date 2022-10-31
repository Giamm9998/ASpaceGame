//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FireRate.h"

FireRate::FireRate() : PowerUp(false) {
    sprite.setColor(sf::Color(132, 70, 240));
}

void FireRate::powerUp(Player &player) const {
    player.getPrimaryCannon().setFireRateMultiplier(player.getPrimaryCannon().getFireRateMultiplier() + 0.25f);
    for (auto &cannon : player.getAuxiliaryCannons())
        cannon.setFireRateMultiplier(cannon.getFireRateMultiplier() + 0.25f);
    player.getPowerUpSound().play();
}