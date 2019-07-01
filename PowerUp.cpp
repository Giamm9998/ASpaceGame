//
// Created by Fabio Luccioletti on 2019-07-01.
//

#include "PowerUp.h"

PowerUp::PowerUp(bool special) : special(special) {}

sf::Sprite PowerUp::getSprite() {
    return sprite;
}
