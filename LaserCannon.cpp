//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "LaserCannon.h"
#include "ResourceManager.h"
#include "Raptor.h"

LaserCannon::LaserCannon() : PowerUp(true) {
    sprite.setColor(sf::Color::Red);
}

void LaserCannon::powerUp(Player &player) const {
    player.setLaserActive(true);
    player.getLaserSound().play();
    std::string textureName = "../Texture/";
    if (typeid(player) == typeid(Raptor)) {
        textureName += "Raptor";
    } else {
        textureName += "Bomber";
    }
    if (!player.getAuxiliaryCannons().empty())
        textureName += "Cannon";
    textureName += "Laser";
    player.getSprite().setTexture(ResourceManager::getTexture(textureName + ".png"));
    player.getPowerUpSound().play();
}
