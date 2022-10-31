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

    const sf::Sprite &getSprite1() const;

    const sf::Sprite &getSprite2() const;

private:
    sf::Sprite sprite1;
    sf::Sprite sprite2;
    float scrollSpeed;

    ///TEST
public:
    float getScrollSpeedTest() const {
        return scrollSpeed;
    }
};


#endif //ASPACEGAME_BACKGROUND_H
