//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "AuxiliaryCannon.h"
#include "ResourceManager.h"

AuxiliaryCannon::AuxiliaryCannon() : PowerUp(true) {
    sprite.setTexture(
            ResourceManager::getTexture("../Texture/AuxiliaryCannonTexture")); //TODO add auxiliary cannon texture
}

void AuxiliaryCannon::powerUp(Player *player) {

}
