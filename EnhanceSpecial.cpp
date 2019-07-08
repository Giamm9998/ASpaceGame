//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "EnhanceSpecial.h"
#include "ResourceManager.h"
#include "Raptor.h"
#include "Bomber.h"
#include "Randomizer.h"
#include "Game.h"

EnhanceSpecial::EnhanceSpecial() : PowerUp(true) {
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

void EnhanceSpecial::powerUp(Player *player) {
    if (typeid(*player) == typeid(Raptor))
        dynamic_cast<Raptor &>(*player).setShieldDuration(dynamic_cast<Raptor &>(*player).getShieldDuration() * 1.5);
    if (typeid(*player) == typeid(Bomber))
        dynamic_cast<Bomber &>(*player).getSecondaryCannon().setFireRateMultiplier(
                dynamic_cast<Bomber &>(*player).getSecondaryCannon().getFireRateMultiplier() * 2);

}
