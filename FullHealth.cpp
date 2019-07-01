//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FullHealth.h"
#include "ResourceManager.h"

FullHealth::FullHealth() : PowerUp(false) {
    sf::Texture texture = ResourceManager::getTexture("Full Health Texture"); //TODO add full health texture
    getSprite().setTexture(texture);
}