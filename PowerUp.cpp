//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include <cmath>
#include "PowerUp.h"
#include "Game.h"
#include "Randomizer.h"

PowerUp::PowerUp(bool special) : special(special), angle(Randomizer::getRandomReal(0.4, 0.8)) {}

sf::Sprite PowerUp::getSprite() {
    return sprite;
}

void PowerUp::move(float dt) {
    if (!(Game::isLegalMove(sprite.getPosition().x, sprite.getScale().x * sprite.getOrigin().x, direction)))
        direction = -direction;
    sprite.move(cos(angle) * powerUpSpeed * dt * direction, sin(angle) * powerUpSpeed * dt);
}

Animator *PowerUp::getAnimator() {
    return animator;
}

PowerUp::~PowerUp() = default;
