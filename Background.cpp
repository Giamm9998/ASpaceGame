//
// Created by gianmarco on 01/07/19.
//
#include "ResourceManager.h"
#include "Background.h"

Background::Background() {
    sprite1.setTexture(ResourceManager::getTexture("../Texture/Background"));//TODO add texture in the folder
    sprite2.setTexture(ResourceManager::getTexture("../Texture/Background"));
    //TODO initialize speed and size
}

void Background::scroll(float dt) {
    sprite1.move(0, scrollSpeed * dt);
    sprite2.move(0, scrollSpeed * dt);
    if (sprite2.getPosition().y == 0) {
        //TODO sprite1.setPosition();
    }
    if (sprite1.getPosition().y == 0) {
        //TODO sprite2.setPosition();
    }
}