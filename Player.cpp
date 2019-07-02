//
// Created by gianmarco on 30/06/19.
//

#include "Player.h"


Player::Player(int hp, int strength, float speed) : Spaceship(hp, strength, speed) {
    sprite.setPosition(0, 500);
    sprite.setOrigin(114, 155);
}

void Player::move(float time, short int direction) {
    sprite.move(speed * time * direction, 0);

}
