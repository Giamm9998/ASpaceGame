//
// Created by gianmarco on 30/06/19.
//

#include "Player.h"
#include "Game.h"


Player::Player(int hp, int strength, float speed) : Spaceship(hp, strength, speed) {
    sprite.setPosition(windowWidth / 2, windowHeight - 60);
}

void Player::move(float time, short int direction) {
    if (Game::isLegalMove(sprite.getPosition().x, sprite.getScale().x * sprite.getOrigin().x, direction)) {
        sprite.move(speed * time * direction, 0);
    }
}
