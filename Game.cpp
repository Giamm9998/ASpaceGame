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


Game::Game() : window(sf::VideoMode(900, 700), "A Space Game"), isPaused(false),
               isMovingLeft(false), isMovingRight(false),
               view((sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))) {


    //Player's spaceship creation
    /*for (int i = 0; i<50; i++) {
        auto *boss = new Boss; //TODO smart pointer
        boss->setPosition(2*i, 200);
        enemyManager.insert(enemyManager.begin(), boss);
    }
    auto* fighter = new Fighter;
    auto* kamikaze = new Kamikaze;
    kamikaze->setPosition(100, 500);
    enemyManager.insert(enemyManager.begin(), fighter);
    enemyManager.insert(enemyManager.begin(), kamikaze);*/





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
    /*if(isMovingRight){
        for(auto &i : enemyManager){
            std::cout<< typeid(*i).name();
            if(typeid(*i) == typeid(Boss)){
                dynamic_cast<Boss&>(*i).move();
            }
            else
                dynamic_cast<Enemy&>(*i).move();
        }
    }

    if(isMovingLeft){
        for(auto &i : enemyManager){
            i->move();
        }
    }*/
    //View updating
    view.setCenter(window.getPosition().x - 85, window.getPosition().y + 250);
    window.setView(view);
}

void Game::render() {
    window.clear(sf::Color::Black);

    for (auto &i : enemyManager) {
        window.draw(dynamic_cast<Enemy &>(*i).getSprite());
    }
    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Left)
        isMovingLeft = isPressed;
    else if (key == sf::Keyboard::Right)
        isMovingRight = isPressed;
}