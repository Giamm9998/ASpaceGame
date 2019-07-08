//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "FireRate.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Randomizer.h"

FireRate::FireRate() : PowerUp(false) { //TODO add fire rate texture
    auto &rotation = animator->createAnimation("Rotation", "../Texture/BasicPowerUp.png", sf::seconds(0.33), true);
    int frames = 16;
    rotation.addFrames(sf::Vector2i(0, 0), sf::Vector2i(128, 128), frames);
    sf::Vector2f distOrigin(sprite.getLocalBounds().width / (2 * frames),
                            sprite.getLocalBounds().height / 2);
    sprite.setOrigin(distOrigin); //TODO add to all the others powerUp
    sprite.setScale(0.3, 0.3);
    sprite.setPosition(Randomizer::getRandomPosition(
            distOrigin.x * sprite.getScale().x, windowWidth - distOrigin.x * sprite.getScale().x,
            -distOrigin.y * sprite.getScale().y, -distOrigin.y * sprite.getScale().y));
    //todo this position may cause isOutOfSight return true on creation
    //animator->update(sf::Time::Zero);
}

void FireRate::powerUp(Player *player) {
    player->setFireRate(player->getFireRate() * 10);
}
