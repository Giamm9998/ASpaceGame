//
// Created by gianmarco on 01/07/19.
//
#include "ResourceManager.h"
#include "Background.h"
#include "Game.h"

Background::Background() {
    sprite1.setTexture(ResourceManager::getTexture("../Texture/Background.png"));
    sprite2.setTexture(ResourceManager::getTexture("../Texture/Background.png"));
    scrollSpeed = 75;
    sprite1.scale(windowWidth / sprite1.getTexture()->getSize().x,
                  windowHeight / sprite1.getTexture()->getSize().y);
    sprite2.scale(sprite1.getScale());
    sprite1.setPosition(0, 0);
    sprite2.setPosition(0, -windowHeight);
}

void Background::scroll(float dt) {
    sprite1.move(0, scrollSpeed * dt);
    sprite2.move(0, scrollSpeed * dt);
    if (sprite2.getPosition().y >= windowHeight) {
        sprite2.setPosition(0, -windowHeight);
    }
    if (sprite1.getPosition().y >= windowHeight) {
        sprite1.setPosition(0, -windowHeight);
    }
}

const sf::Sprite &Background::getSprite1() const {
    return sprite1;
}

const sf::Sprite &Background::getSprite2() const {
    return sprite2;
}
