//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "EnhanceSpecial.h"
#include "ResourceManager.h"

EnhanceSpecial::EnhanceSpecial() : PowerUp(true) {
    sf::Texture texture = ResourceManager::getTexture("Enhance Special Texture"); //TODO add enhance special texture
    getSprite().setTexture(texture);
}
