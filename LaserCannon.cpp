//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "LaserCannon.h"
#include "ResourceManager.h"

LaserCannon::LaserCannon() : PowerUp(true) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/LaserCannonTexture")); //TODO add laser cannon texture
}

void LaserCannon::powerUp(Player *player) {

}
