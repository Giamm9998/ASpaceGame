//
// Created by gianmarco on 30/06/19.
//

#include "Raptor.h"
#include "ResourceManager.h"

Raptor::Raptor() : Player(100, 8, 40) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Raptor"));
}

void Raptor::useSpecialPower() {

}
