//
// Created by gianmarco on 30/06/19.
//

#include "ResourceManager.h"
#include "Raptor.h"
#include "Player.h"
#include "Game.h"
#include "Spaceship.h"


Player::Player(int hp, int strength, float speed, int maxHp) : Spaceship(hp, strength, speed), maxHp(maxHp),
                                                               charging(false) {
    sprite.setPosition(static_cast<float>(windowWidth) / 2,
                       windowHeight - 60); //todo set position not based on constants
}

void Player::move(float time, short int direction) {
    if (Game::isLegalMove(sprite.getPosition().x, sprite.getScale().x * sprite.getOrigin().x, direction)) {
        sprite.move(speed * time * direction, 0);
        boundingBox.move(speed * time * direction, 0);
    }
}

int Player::getMaxHp() const {
    return maxHp;
}


bool Player::isCharging() const {
    return charging;
}

void Player::receiveDamage(int damage) {
    if (!receivingDamage)
        Spaceship::receiveDamage(damage);
}
