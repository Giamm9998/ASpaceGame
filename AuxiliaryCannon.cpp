//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "AuxiliaryCannon.h"
#include "ResourceManager.h"
#include "Raptor.h"

AuxiliaryCannon::AuxiliaryCannon() : PowerUp(true) {
    sprite.setColor(sf::Color::Green);
}

void AuxiliaryCannon::powerUp(Player &player) const {
    Cannon cannon(player.getPrimaryCannon());
    if (player.getAuxiliaryCannons().empty()) {
        sf::Vector2f relativePosition;
        std::string textureName = "../Texture/";
        if (typeid(player) == typeid(Raptor)) {
            textureName += "Raptor";
            relativePosition = sf::Vector2f(76, 0);
        } else {
            textureName += "Bomber";
            relativePosition = sf::Vector2f(106, 0);
        }
        textureName += "Cannon";
        if (player.isLaserActive())
            textureName += "Laser";

        player.getSprite().setTexture(ResourceManager::getTexture(textureName + ".png"));
        cannon.setLocalRelativePosition(relativePosition);
        player.getPrimaryCannon().setLocalRelativePosition(-relativePosition);
        player.getAuxiliaryCannons().push_back(cannon);
    } else if (player.getAuxiliaryCannons().size() < 2) {
        cannon.setLocalRelativePosition(sf::Vector2f(0, 0));
        player.getAuxiliaryCannons().push_back(cannon);
    }
}
