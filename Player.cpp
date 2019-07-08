//
// Created by gianmarco on 30/06/19.
//

#include "ResourceManager.h"
#include "Raptor.h"
#include "Player.h"
#include "Game.h"
#include "Spaceship.h"


Player::Player(float hp, float strength, float speed, float fireRate, float maxHp) : Spaceship(hp, strength, speed,
                                                                                               fireRate), maxHp(maxHp),
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

float Player::getMaxHp() const {
    return maxHp;
}


bool Player::isCharging() const {
    return charging;
}

void Player::receiveDamage(float damage) {
    if (!receivingDamage)
        Spaceship::receiveDamage(damage);
}

std::vector<Cannon> &Player::getAuxiliaryCannons() {
    return auxiliaryCannons;
}

void Player::setStrength(float strength) {
    Spaceship::setStrength(strength);
    primaryCannon.getProjectilePrototype().setDamage(strength * primaryCannon.getStrengthMultiplier());
    for (auto &cannon : auxiliaryCannons) {
        cannon.getProjectilePrototype().setDamage(strength * cannon.getStrengthMultiplier());
    }
}
