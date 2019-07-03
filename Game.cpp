//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include <iostream>
#include "Game.h"
#include "ResourceManager.h"
#include "Bomber.h"
#include "Kamikaze.h"
#include "Fighter.h"
#include "Boss.h"
#include "Minion.h"
#include "Assaulter.h"
#include "Raptor.h"
#include "Background.h"

#define RIGHT 1
#define LEFT -1

Game::Game() : window(sf::VideoMode(900, 700), "A Space Game"), isPaused(false),
               isMovingLeft(false), isMovingRight(false),
               view((sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))) {


    //Player's spaceship creation
    for (int i = 0; i < 5; i++) {
        auto *boss = new Boss; //TODO smart pointer
        boss->setPosition(50 * i - 200, 200);
        enemyManager.insert(enemyManager.begin(), boss);
    }

    auto *boss = new Boss;
    auto *fighter = new Fighter;
    auto *kamikaze = new Kamikaze;
    auto *minion = new Minion;
    auto *assaulter = new Assaulter;

    kamikaze->setPosition(0, 500);
    minion->setPosition(-100, 400);
    assaulter->setPosition(200, 400);
    boss->setPosition(300, 200);
    enemyManager.insert(enemyManager.begin(), fighter);
    enemyManager.insert(enemyManager.begin(), kamikaze);
    enemyManager.insert(enemyManager.begin(), minion);
    enemyManager.insert(enemyManager.begin(), assaulter);
    enemyManager.insert(enemyManager.begin(), boss);


    player = new Raptor;
    background = new Background;



    //Background creation

    //Limitation of the framerate
    window.setFramerateLimit(60);
}

void Game::run() {
    sf::Clock clock;
    sf::Time deltaTime;
    while (window.isOpen()) {
        deltaTime = clock.restart();
        processEvents();
        if (!isPaused)
            update(deltaTime);
        render();

    }

}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::GainedFocus:
                isPaused = false;
                break;
            case sf::Event::LostFocus:
                isPaused = true;
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time dt) {
    //Player movement
    float time = dt.asSeconds();
    for (auto &i : enemyManager) {
        if (typeid(*i) == typeid(Minion))
            dynamic_cast<Minion &>(*i).move(time);
        else if (typeid(*i) == typeid(Boss))
            dynamic_cast<Boss &>(*i).move(time);
        else if (typeid(*i) == typeid(Kamikaze))
            dynamic_cast<Kamikaze &>(*i).move(time);
        else if (typeid(*i) == typeid(Fighter))
            dynamic_cast<Fighter &>(*i).move(time);
        else if (typeid(*i) == typeid(Assaulter))
            dynamic_cast<Assaulter &>(*i).move(time);
    }
    if (isMovingRight)
        player->move(time, RIGHT);

    if (isMovingLeft)
        player->move(time, LEFT);

    //View updating
    view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    window.setView(view);
}

void Game::render() {
    window.clear(sf::Color::Black);

    window.draw(background->getSprite1());
    for (auto &i : enemyManager) {
        window.draw(dynamic_cast<Enemy &>(*i).getSprite());
    }
    window.draw(player->getSprite());
    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Left)
        isMovingLeft = isPressed;
    else if (key == sf::Keyboard::Right)
        isMovingRight = isPressed;
}