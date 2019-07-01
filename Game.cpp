//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include "Game.h"
#include "ResourceManager.h"


Game::Game() : window(sf::VideoMode(900, 700), "A Space Game"), isPaused(false),
               isMovingLeft(false), isMovingRight(false),
               view((sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))) {


    //Player's spaceship creation

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

    //View updating
    view.setCenter(window.getPosition().x - 85, window.getPosition().y + 250);
    window.setView(view);
}

void Game::render() {
    window.clear(sf::Color::Black);

    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Left)
        isMovingLeft = isPressed;
    else if (key == sf::Keyboard::Right)
        isMovingRight = isPressed;
}