//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FireRate.h"
#include "ResourceManager.h"

FireRate::FireRate() : PowerUp(false) {
    sf::Texture texture = ResourceManager::getTexture("Fire Rate Texture"); //TODO add fire rate texture
    getSprite().setTexture(texture);
}
