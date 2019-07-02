//
// Created by gianmarco on 01/07/19.
//

#ifndef ASPACEGAME_BACKGROUND_H
#define ASPACEGAME_BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background {
public:
    explicit Background();

    void scroll(float dt);

private:
    sf::Vector2f size;
    sf::Sprite sprite1;
    sf::Sprite sprite2;
    float scrollSpeed;
};


#endif //ASPACEGAME_BACKGROUND_H
