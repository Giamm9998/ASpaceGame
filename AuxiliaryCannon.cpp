//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "AuxiliaryCannon.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Randomizer.h"

AuxiliaryCannon::AuxiliaryCannon() : PowerUp(true) {
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
}

void AuxiliaryCannon::powerUp(Player *player) {
    Cannon cannon(player->getPrimaryCannon());
    if (player->getAuxiliaryCannons().empty()) {
        player->getSprite().setTexture(ResourceManager::getTexture("../Texture/RaptorCannon.png"));
        sf::Vector2f relativePosition(76, 0);
        cannon.setRelativePosition(relativePosition);
        player->getPrimaryCannon().setRelativePosition(sf::Vector2f(-76, 0));
        player->getAuxiliaryCannons().push_back(cannon);
    } else if (player->getAuxiliaryCannons().size() < 2) {
        sf::Vector2f relativePosition(0, 0);
        cannon.setRelativePosition(relativePosition);
        player->getAuxiliaryCannons().push_back(cannon);
    }
}
