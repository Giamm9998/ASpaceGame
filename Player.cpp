//
// Created by gianmarco on 30/06/19.
//

#include "Player.h"
#include "Game.h"


Player::Player(int hp, int strength, float speed, int maxHp) : Spaceship(hp, strength, speed), maxHp(maxHp) {
    sprite.setPosition(static_cast<float>(windowWidth) / 2, windowHeight - 60);
}

void Player::move(float time, short int direction) {
    if (Game::isLegalMove(sprite.getPosition().x, sprite.getScale().x * sprite.getOrigin().x, direction)) {
        sprite.move(speed * time * direction, 0);
    }
}

int Player::getMaxHp() const {
    return maxHp;
}
