//
// Created by gianmarco on 01/07/19.
//
#include "ResourceManager.h"
#include "Background.h"

Background::Background(sf::Vector2f size, sf::Texture *texture) : size(size) {
    sprite.setTexture(ResourceManager::getTexture("Background"));//TODO add texture in the folder
}
