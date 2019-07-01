//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "LaserCannon.h"
#include "ResourceManager.h"

LaserCannon::LaserCannon() : PowerUp(true) {
    sf::Texture texture = ResourceManager::getTexture("Laser Cannon Texture"); //TODO add laser cannon texture
    getSprite().setTexture(texture);
}
