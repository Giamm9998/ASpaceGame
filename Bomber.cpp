//
// Created by gianmarco on 30/06/19.
//

#include "Bomber.h"
#include "ResourceManager.h"

Bomber::Bomber() : Player(150, 10, 5) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Bomber"));
    //TODO initialize secondaryCannon
}