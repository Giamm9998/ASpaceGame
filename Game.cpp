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
#include <memory>

Game::Game() : window(sf::VideoMode(windowWidth, windowHeight), "A Space Game"), isPaused(false),
               isMovingLeft(false), isMovingRight(false), isShooting(false),
               view((sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))) {


    //Player's spaceship creation
    /*for (int i = 0; i < 5; i++) {
        auto *boss = new Boss; //TODO smart pointer
        boss->setPosition(50 * i, 200);
        enemyManager.insert(enemyManager.begin(), boss);
    }*/

    auto *boss = new Boss;
    auto *fighter = new Fighter;
    auto *kamikaze = new Kamikaze;
    auto *minion = new Minion;
    auto *assaulter = new Assaulter;

    kamikaze->setPosition(0, 500);
    enemyManager.insert(enemyManager.begin(), fighter);
    enemyManager.insert(enemyManager.begin(), kamikaze);
    enemyManager.insert(enemyManager.begin(), minion);
    enemyManager.insert(enemyManager.begin(), assaulter);
    enemyManager.insert(enemyManager.begin(), boss);


    player = new Raptor;

    //Background creation
    background = new Background;

    //Limitation of the framerate
    window.setFramerateLimit(60);

    animator = new Animator(explosion);
    auto &boom = animator->createAnimation("Boom", "../Texture/Explosion.png", sf::seconds(1), true);
    boom.addFrames(sf::Vector2i(0, 0), sf::Vector2i(128, 128), 8, 8);
    explosion.setPosition(100, 100);
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

    animator->update(dt);
    //Player movement
    float time = dt.asSeconds();
    updateEnemies(time);
    updatePlayer(time);
    updateProjectiles(time);

    background->scroll(time);
    //View updating
    view.setCenter(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2);
    window.setView(view);
}

void Game::render() {
    window.clear(sf::Color::Black);

    window.draw(background->getSprite1());
    window.draw(background->getSprite2());


    for (auto &i : enemyManager) {
        window.draw(dynamic_cast<Enemy &>(*i).getSprite());
    }

    window.draw(player->getSprite());
    if (isUsingSpecial) {
        if (typeid(*player) == typeid(Raptor)) {
            window.draw(dynamic_cast<Raptor &>(*player).getShield());
        }
    }

    for (auto &i : projectileManager) {
        window.draw(i->getSprite());
    }

    window.draw(explosion);
    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Left)
        isMovingLeft = isPressed;
    else if (key == sf::Keyboard::Right)
        isMovingRight = isPressed;
    else if (key == sf::Keyboard::Z)
        isShooting = isPressed;
    else if (key == sf::Keyboard::Q)
        isUsingSpecial = isPressed;
}

bool Game::isLegalMove(float x, float origin, short int direction) {
    return !((x <= origin && direction == left) || (x >= windowWidth - origin && direction == right));
}

void Game::updatePlayer(float time) {
    if (isMovingRight)
        player->move(time, right);

    if (isMovingLeft)
        player->move(time, left);

    if (isShooting) {
        std::unique_ptr<Projectile> projectile = player->useCannon(time, &(player->getPrimaryCannon()));
        emplaceProj(std::move(projectile));
    }
}

void Game::updateEnemies(float time) {
    for (auto &i : enemyManager) {
        std::unique_ptr<Projectile> projectile;
        if (typeid(*i) == typeid(Minion)) {
            dynamic_cast<Minion &>(*i).move(time);
            projectile = dynamic_cast<Minion &>(*i).useCannon(time, &(i->getPrimaryCannon()));
            emplaceProj(std::move(projectile));

        } else if (typeid(*i) == typeid(Boss)) {
            dynamic_cast<Boss &>(*i).move(time);
            projectile = dynamic_cast<Boss &>(*i).useCannon(time, &(i->getPrimaryCannon()));
            emplaceProj(std::move(projectile));

        } else if (typeid(*i) == typeid(Kamikaze)) {
            dynamic_cast<Kamikaze &>(*i).move(time);
            projectile = dynamic_cast<Kamikaze &>(*i).useCannon(time, &(i->getPrimaryCannon()));
            emplaceProj(std::move(projectile));

        } else if (typeid(*i) == typeid(Fighter)) {
            dynamic_cast<Fighter &>(*i).move(time);
            projectile = dynamic_cast<Fighter &>(*i).useCannon(time, &(i->getPrimaryCannon()));
            emplaceProj(std::move(projectile));
            for (auto &j : dynamic_cast<Fighter &>(*i).getExternalCannons()) {
                Cannon *cannon = &j;
                projectile = dynamic_cast<Fighter &>(*i).useCannon(time, cannon);
                emplaceProj(std::move(projectile));
            }
        } else if (typeid(*i) == typeid(Assaulter)) {
            dynamic_cast<Assaulter &>(*i).move(time);
            projectile = dynamic_cast<Assaulter &>(*i).useCannon(time, &(i->getPrimaryCannon()),
                                                                 player->getSprite().getPosition());
            emplaceProj(std::move(projectile));
        }

    }
}

void Game::emplaceProj(std::unique_ptr<Projectile> projectile) {
    if (projectile != nullptr)
        projectileManager.emplace_back(new Projectile(*projectile));
}

void Game::updateProjectiles(float time) {
    for (auto &l : projectileManager) //TODO free the memory when projectile is out of screen
        l->move(time);
}
