//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "EnhanceSpecial.h"
#include "ResourceManager.h"
#include "Raptor.h"
#include "Bomber.h"

EnhanceSpecial::EnhanceSpecial() : PowerUp(true) {}

void EnhanceSpecial::powerUp(Player &player) const {
    if (typeid(player) == typeid(Raptor)) {
        dynamic_cast<Raptor &>(player).setShieldDuration(
                dynamic_cast<Raptor &>(player).getShieldDuration() * 1.2f);
        player.setElapsedTime(0);
        player.setCharging(false);
    }
    if (typeid(player) == typeid(Bomber)) {
        dynamic_cast<Bomber &>(player).getSecondaryCannon().setFireRateMultiplier(
                dynamic_cast<Bomber &>(player).getSecondaryCannon().getFireRateMultiplier() * 1.5f);
    }
    player.getPowerUpSound().play();
}
