//
// Created by gianmarco on 01/07/19.
//
#include "ResourceManager.h"
#include "Background.h"

#define WINDOW_HEIGTH 675

Background::Background() {
    sprite1.setTexture(ResourceManager::getTexture("../Texture/Background.png"));
    sprite2.setTexture(ResourceManager::getTexture("../Texture/Background.png"));
    scrollSpeed = 75;
    sprite1.scale(0.5625, 0.5625);
    sprite2.scale(0.5625, 0.5625);
    sprite1.setPosition(0, 0);
    sprite2.setPosition(0, -WINDOW_HEIGTH);
}

void Background::scroll(float dt) {
    sprite1.move(0, scrollSpeed * dt);
    sprite2.move(0, scrollSpeed * dt);
    if (sprite2.getPosition().y >= WINDOW_HEIGTH) {
        sprite2.setPosition(0, -WINDOW_HEIGTH);
    }
    if (sprite1.getPosition().y >= WINDOW_HEIGTH) {
        sprite1.setPosition(0, -WINDOW_HEIGTH);
    }
}

const sf::Sprite &Background::getSprite1() const {
    return sprite1;
}

const sf::Sprite &Background::getSprite2() const {
    return sprite2;
}

float Background::getScrollSpeed() const {
    return scrollSpeed;
}
