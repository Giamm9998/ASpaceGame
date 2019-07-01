//
// Created by Fabio Luccioletti on 2019-07-01.
//

#ifndef ASPACEGAME_POWERUP_H
#define ASPACEGAME_POWERUP_H


#include <SFML/Graphics.hpp>

class PowerUp {
public:
    PowerUp(bool special);

    void move();

    virtual void powerUp() = 0;

    sf::Sprite getSprite();

private:
    bool special;
    sf::Sprite sprite;
};


#endif //ASPACEGAME_POWERUP_H
