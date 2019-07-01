//
// Created by gianmarco on 01/07/19.
//

#ifndef ASPACEGAME_BACKGROUND_H
#define ASPACEGAME_BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background {
public:
    Background(sf::Vector2f size, sf::Texture *texture);

    void scroll();

private:
    sf::Vector2f size;
    sf::Sprite sprite;
};


#endif //ASPACEGAME_BACKGROUND_H
