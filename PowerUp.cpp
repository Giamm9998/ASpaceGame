//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include <cmath>
#include "PowerUp.h"
#include "Game.h"
#include "Randomizer.h"

PowerUp::PowerUp(bool special) : special(special), angle(Randomizer::getRandomReal(powerUpMinAngle, powerUpMaxAngle)) {
    auto &rotation = animator->createAnimation("Rotation", "../Texture/BasicPowerUp.png", sf::seconds(0.33), true);
    unsigned int frames = 16;
    rotation.addFrames(sf::Vector2i(0, 0), sf::Vector2i(128, 128), frames);
    sf::Vector2f distOrigin(sprite.getLocalBounds().width / (2 * frames),
                            sprite.getLocalBounds().height / 2);
    direction = Randomizer::getRandomInt(0, 1) ? -1 : 1;
    sprite.setOrigin(distOrigin);
    sprite.setScale(0.3, 0.3);
    sprite.setPosition(Randomizer::getRandomPosition(
            distOrigin.x * sprite.getScale().x, windowWidth - distOrigin.x * sprite.getScale().x,
            -distOrigin.y * sprite.getScale().y, -distOrigin.y * sprite.getScale().y));
}

sf::Sprite &PowerUp::getSprite() {
    return sprite;
}

void PowerUp::move(float dt) {
    if (!(Game::isLegalMove(sprite.getPosition().x, sprite.getScale().x * sprite.getOrigin().x, direction)))
        direction = -direction;
    sprite.move(cos(angle) * powerUpSpeed * dt * direction, sin(angle) * powerUpSpeed * dt);
}

Animator *PowerUp::getAnimator() const { //todo smart pointer/reference
    return animator;
}

PowerUp::~PowerUp() {
    delete animator;
}
