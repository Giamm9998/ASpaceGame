//
// Created by gianmarco on 01/07/19.
//
#include "ResourceManager.h"
#include "Background.h"

Background::Background() {
    sprite1.setTexture(ResourceManager::getTexture("../Texture/Background.png"));//TODO add texture in the folder
    sprite2.setTexture(ResourceManager::getTexture("../Texture/Background.png"));
    sprite1.scale(0.7, 0.7);
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

const sf::Sprite &Background::getSprite1() const {
    return sprite1;
}

const sf::Sprite &Background::getSprite2() const {
    return sprite2;
}
