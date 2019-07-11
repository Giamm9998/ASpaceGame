//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include <iostream>
#include "Game.h"
#include "ResourceManager.h"
#include "Raptor.h"
#include <cmath>

Game::Game() : window(sf::VideoMode(windowWidth, windowHeight), "A Space Game"), isPaused(false),
               isMovingLeft(false), isMovingRight(false), isShooting(false), isUsingSpecial(false),
               score(0), view((sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))) {

    createHud();

    background = std::unique_ptr<Background>(new Background);

    window.setFramerateLimit(60);
}

void Game::createHud() {
    specialHud.setSize(sf::Vector2f(10, 100));
    specialHud.setPosition(400, windowHeight - 5);
    specialHud.rotate(-90.f);
    specialHud.setFillColor(sf::Color::Red);
    specialHudOutline = specialHud;
    specialHudOutline.setFillColor(sf::Color(255, 255, 255, 0));
    specialHudOutline.setOutlineThickness(2);
    specialHudOutline.setOutlineColor(sf::Color(173, 161, 161, 255));

    hud.setSize(sf::Vector2f(windowWidth, 20));
    hud.setFillColor(sf::Color::Black);
    hud.setPosition(0, windowHeight - hud.getSize().y);
    hud.setOutlineThickness(2);
    hud.setOutlineColor(sf::Color(173, 161, 161, 255));

    hpHud.setSize(sf::Vector2f(10, 100));
    hpHud.setPosition(100, windowHeight - 5);
    hpHud.rotate(-90.f);
    hpHud.setFillColor(sf::Color::Red);
    hpHudOutline = hpHud;
    hpHudOutline.setFillColor(sf::Color(255, 255, 255, 0));
    hpHudOutline.setOutlineThickness(2);
    hpHudOutline.setOutlineColor(sf::Color(173, 161, 161, 255));

    sf::Text text("Score: " + std::to_string(score), ResourceManager::getFont("../font/venus rising rg.ttf"));
    text.setScale(0.7, 0.7);
    scoreText = text;
    scoreText.setPosition(600, windowHeight - 25);
    text.setString("HP");
    hpText = text;
    hpText.setPosition(50, windowHeight - 25);
    text.setString("Special");
    specialText = text;
    specialText.setPosition(260, windowHeight - 25);
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
    sf::Event event{};
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

void Game::update(const sf::Time &dt) {

    float time = dt.asSeconds();
    entityManager.updateAsteroids(time, score, isUsingSpecial);
    entityManager.updateEnemies(time, score);
    entityManager.updatePlayer(time, isMovingRight, isMovingLeft, isShooting, isUsingSpecial, specialHud, hpHud);
    entityManager.updateProjectiles(time, isUsingSpecial);
    entityManager.updatePowerUp(time);

    scoreText.setString("Score: " + std::to_string(score));
    background->scroll(time);

    //View updating
    view.setCenter(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2);
    window.setView(view);
}

void Game::render() {
    window.clear(sf::Color::Black);

    drawBackground();
    draw<Asteroid>(entityManager.getAsteroidManager());
    draw<Spaceship>(entityManager.getEnemyManager());
    draw<Projectile>(entityManager.getProjectileManager());
    drawPlayer();
    drawPowerUp();
    drawHud();

    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Left)
        isMovingLeft = isPressed;
    else if (key == sf::Keyboard::Right)
        isMovingRight = isPressed;
    else if (key == sf::Keyboard::Z)
        isShooting = isPressed;
    else if (key == sf::Keyboard::X)
        isUsingSpecial = isPressed;
}

void Game::drawPowerUp() {
    auto &powerUp = entityManager.getPowerUp();
    if (powerUp != nullptr)
        window.draw(powerUp->getSprite());
}

void Game::drawPlayer() {
    auto &player = entityManager.getPlayer();
    window.draw(player->getSprite());

    if (isUsingSpecial) {
        auto &playerType = *(player.get());
        if (typeid(playerType) == typeid(Raptor))
            window.draw(dynamic_cast<Raptor &>(playerType).getShield());
    }

    if (player->isLaserActive())
        window.draw(player->getLaser());
}

void Game::drawBackground() {
    window.draw(background->getSprite1());
    window.draw(background->getSprite2());
}

template<typename T>
void Game::draw(const std::list<std::unique_ptr<T>> &list) {
    for (auto &entity: list)
        window.draw(entity->getSprite());
}

void Game::drawHud() {
    window.draw(hud);
    window.draw(specialHud);
    window.draw(specialHudOutline);
    window.draw(hpHud);
    window.draw(hpHudOutline);
    window.draw(scoreText);
    window.draw(hpText);
    window.draw(specialText);
}

bool Game::isLegalMove(float x, float origin, short int direction) { // todo &sprite instead of x and origin
    return !((x <= origin && direction == left) || (x >= windowWidth - origin && direction == right));
}
