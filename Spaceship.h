//
// Created by gianmarco on 30/06/19.
//

#ifndef ASPACEGAME_SPACESHIP_H
#define ASPACEGAME_SPACESHIP_H


#include <SFML/Graphics.hpp>

class Spaceship {
public:
    Spaceship(int hp, int strength, float speed);

    virtual void move() = 0;

    void useCannon();

    void receiveDamage();

    int getHp() const;

    void setHp(int hp);

    int getStrength() const;

    void setStrength(int strength);

    float getSpeed() const;

    void setSpeed(float speed);

    sf::Sprite getSprite();


private:
    int hp;
    int strength;
    float speed;
    sf::Sprite sprite;
    //Cannon primaryCannon;
};


#endif //ASPACEGAME_SPACESHIP_H
