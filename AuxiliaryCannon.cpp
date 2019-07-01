//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "AuxiliaryCannon.h"
#include "ResourceManager.h"

AuxiliaryCannon::AuxiliaryCannon() : PowerUp(true) {
    sf::Texture texture = ResourceManager::getTexture("Auxiliary Cannon Texture"); //TODO add auxiliary cannon texture
    getSprite().setTexture(texture);
}