//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "Speed.h"
#include "ResourceManager.h"

Speed::Speed() : PowerUp(false) {
    sf::Texture texture = ResourceManager::getTexture("Speed Texture"); //TODO add speed texture
    getSprite().setTexture(texture);
}
