//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include <iostream>
#include "Game.h"
#include "ResourceManager.h"
#include "Raptor.h"
#include "Kamikaze.h"
#include "Bomber.h"
#include <cmath>

Game::Game() : window(sf::VideoMode(static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)),
                      "A Space Game"), isPaused(false), isMovingLeft(false), isMovingRight(false), isShooting(false),
               isChoosingPlayer(true),
               isUsingSpecial(false), view((sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))),
               achievement(&entityManager) {

    createHud();

    achievement.attach();
    achievementDuration = 0;

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

    sf::Text text("Score: " + std::to_string(entityManager.getScore()), ResourceManager::getFont("../font/font.ttf"));
    text.setScale(0.7, 0.7);
    scoreText = text;
    scoreText.setPosition(600, windowHeight - 25);
    text.setString("HP");
    hpText = text;
    hpText.setPosition(50, windowHeight - 25);
    text.setString("Special");
    specialText = text;
    specialText.setPosition(260, windowHeight - 25);
    text.setString("Selezionare il tipo del personaggio:\n\nA: Bomber                              S:Raptor");
    playerSelection = text;
    playerSelection.setPosition(150, 200);
    playerSelection.setFillColor(sf::Color::Red);

    bomberSprite.setTexture(ResourceManager::getTexture("../Texture/BomberBasic.png"));
    bomberSprite.setScale(0.35, 0.35);
    bomberSprite.setPosition(180, 280);
    raptorSprite.setTexture(ResourceManager::getTexture("../Texture/RaptorBasic.png"));
    raptorSprite.setScale(0.35, 0.35);
    raptorSprite.setPosition(600, 280);
}

void Game::run() {
    sf::Clock clock;
    sf::Time deltaTime;
    while (window.isOpen()) {
        deltaTime = clock.restart();
        processEvents();
        if (!isPaused && !isChoosingPlayer)
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
    entityManager.updateAsteroids(time, isUsingSpecial);
    entityManager.updateEnemies(time);
    entityManager.updatePlayer(time, isMovingRight, isMovingLeft, isShooting, isUsingSpecial, specialHud, hpHud);
    entityManager.updateProjectiles(time, isUsingSpecial);
    entityManager.updatePowerUp(time);

    scoreText.setString("Score: " + std::to_string(entityManager.getScore()));
    updateAchievement(time);
    background->scroll(time);

    //View updating
    view.setCenter(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2);
    window.setView(view);
}

void Game::render() {
    window.clear(sf::Color::Black);

    drawBackground();
    if (!isChoosingPlayer) {
        draw<Asteroid>(entityManager.getAsteroidManager());
        draw<Projectile>(entityManager.getProjectileManager());
        drawEnemy();
        drawPlayer();
        drawPowerUp();
        drawHud();
    } else {
        window.draw(playerSelection);
        window.draw(bomberSprite);
        window.draw(raptorSprite);
    }
    if (achievement.isAppearing())
        window.draw(achievement.getSprite());
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
    else if (key == sf::Keyboard::A && isChoosingPlayer) {
        entityManager.selectPlayer<Bomber>();
        isChoosingPlayer = false;
    } else if (key == sf::Keyboard::S && isChoosingPlayer) {
        entityManager.selectPlayer<Raptor>();
        isChoosingPlayer = false;
    }

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

void Game::drawEnemy() {
    for (auto &enemy: entityManager.getEnemyManager()) {

        auto &enemyType = *(enemy.get());
        window.draw(enemy->getSprite());
        if (enemy->getHp() <= 0)
            for (auto &explosion : dynamic_cast<Enemy &>(*enemy).getExplosions())
                window.draw(explosion);
        else {
            if (typeid(enemyType) == typeid(Kamikaze)) {
                if (dynamic_cast<Kamikaze &>(*enemy).isAttacking()) {
                    window.draw(dynamic_cast<Kamikaze &>(*enemy).getBeamBorderLeft());
                    window.draw(dynamic_cast<Kamikaze &>(*enemy).getBeamBorderRight());
                    window.draw(dynamic_cast<Kamikaze &>(*enemy).getBeam());
                }
            }
        }
    }
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

void Game::updateAchievement(float time) {
    if (achievement.isAppearing()) {
        achievementDuration += time;
        if (achievementDuration > 2) {
            achievementDuration = 0;
            achievement.setAppearing(false);
        }
    }
}
