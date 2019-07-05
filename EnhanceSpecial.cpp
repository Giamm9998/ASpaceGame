//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "EnhanceSpecial.h"
#include "ResourceManager.h"

EnhanceSpecial::EnhanceSpecial() : PowerUp(true) {
    sprite.setTexture(
            ResourceManager::getTexture("../Texture/EnhanceSpecialTexture")); //TODO add enhance special texture
}

void EnhanceSpecial::powerUp(Player *player) {

}
