//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "Strength.h"
#include "ResourceManager.h"


Strength::Strength() : PowerUp(false) {
    sf::Texture texture = ResourceManager::getTexture("Strength Texture"); //TODO add strength texture
    getSprite().setTexture(texture);
}

