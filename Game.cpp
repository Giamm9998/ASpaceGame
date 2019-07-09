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
#include "FireRate.h"
#include "Speed.h"
#include "Asteroid.h"
#include "Player.h"
#include "Spaceship.h"
#include "EnhanceSpecial.h"
#include "AuxiliaryCannon.h"
#include "Strength.h"
#include "LaserCannon.h"
#include <memory>
#include <math.h>

Game::Game() : window(sf::VideoMode(windowWidth, windowHeight), "A Space Game"), isPaused(false),
               isMovingLeft(false), isMovingRight(false), isShooting(false), isUsingSpecial(false),
               score(0), view((sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))) {
    createHud();

    enemyManager.emplace_back(new Fighter);
    enemyManager.emplace_back(new Kamikaze);
    enemyManager.emplace_back(new Minion);
    enemyManager.emplace_back(new Assaulter);
    enemyManager.emplace_back(new Boss);

    player = std::unique_ptr<Player>(new Raptor);

    powerUp = std::unique_ptr<PowerUp>(new LaserCannon);

    for (int i = 0; i < 100; i++)
        asteroidManager.emplace_back(new Asteroid);

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

void Game::update(sf::Time dt) {

    //Player movement
    float time = dt.asSeconds();
    updateAsteroids(time);
    updateEnemies(time);
    updatePlayer(time);
    updateProjectiles(time);
    updatePowerUp(time);

    scoreText.setString("Score: " + std::to_string(score));
    background->scroll(time);

    //View updating
    view.setCenter(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2);
    window.setView(view);
}

void Game::render() {
    window.clear(sf::Color::Black);

    drawBackground();
    drawAsteroids();
    drawPlayer();
    drawEnemies();
    drawProjectiles();
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
    else if (key == sf::Keyboard::Q)
        isUsingSpecial = isPressed;
}

void Game::updatePowerUp(float time) {
    if (powerUp != nullptr) {
        powerUp->getAnimator()->update(time);
        powerUp->move(time);
        if (isOutOfSigth(powerUp->getSprite())) {
            powerUp.reset(new FireRate);
        } else if (powerUp->getSprite().getGlobalBounds().intersects(player->getBoundingBox().getGlobalBounds())) {
            powerUp->powerUp(player.get());
            powerUp.reset(new AuxiliaryCannon);
        }
    }
}

void Game::updatePlayer(float time) {
    if (player->isReceivingDamage()) {
        player->blink(time);
        hpHud.setScale(1, std::max(0.f, (player->getHp() / player->getMaxHp())));
    }

    if (isMovingRight)
        player->move(time, right);

    if (isMovingLeft)
        player->move(time, left);

    if (isShooting) {
        emplaceProjectile(player->useCannon(time, &(player->getPrimaryCannon())));
        for (auto &auxiliaryCannon : player->getAuxiliaryCannons())
            emplaceProjectile(player->useCannon(time, &auxiliaryCannon));
    }

    auto &playerType = *player;
    if (isUsingSpecial) {
        if (typeid(playerType) == typeid(Bomber)) {
            if (!player->isCharging())
                emplaceProjectile(dynamic_cast<Bomber &>(*player).useBomb(time, specialHud));
        }
        if (typeid(playerType) == typeid(Raptor)) {
            if (!player->isCharging())
                dynamic_cast<Raptor &>(*player).useShield(time, specialHud);
        }
    }

    if (typeid(playerType) == typeid(Bomber)) {
        if (player->isCharging())
            dynamic_cast<Bomber &>(*player).recharge(time, specialHud);
    }
    if (typeid(playerType) == typeid(Raptor)) {
        if (player->isCharging())
            dynamic_cast<Raptor &>(*player).recharge(time, specialHud);
    }

    if (player->isLaserActive())
        checkForLaserCollision(time);
}

void Game::updateEnemies(float time) {
    for (auto enemyIter = enemyManager.begin(); enemyIter != enemyManager.end();) {
        auto enemy = (*enemyIter).get();
        if ((enemy)->getHp() <= 0) {
            if ((enemy)->die(time)) {
                score += static_cast<int>(enemy->getMaxHp());
                enemyManager.erase(enemyIter++);
            }
            else
                enemyIter++;
        } else {
            enemyIter++;
            if ((enemy)->isReceivingDamage())
                (enemy)->blink(time);

            std::unique_ptr<Projectile> projectile;

            if (typeid(*enemy) == typeid(Minion)) {
                dynamic_cast<Minion &>(*enemy).move(time);
                emplaceProjectile(dynamic_cast<Minion &>(*(enemy)).useCannon(time, &enemy->getPrimaryCannon()));
            } else if (typeid(*enemy) == typeid(Boss)) {
                dynamic_cast<Boss &>(*enemy).move(time);
                //emplaceProjectile(dynamic_cast<Boss &>(*enemy).useCannon(time, &enemy->getPrimaryCannon()));
            } else if (typeid(*enemy) == typeid(Kamikaze)) {
                dynamic_cast<Kamikaze &>(*enemy).move(time);
                emplaceProjectile(dynamic_cast<Kamikaze &>(*enemy).useCannon(time, &enemy->getPrimaryCannon()));
            } else if (typeid(*enemy) == typeid(Fighter)) {
                dynamic_cast<Fighter &>(*enemy).move(time);
                emplaceProjectile(dynamic_cast<Fighter &>(*enemy).useCannon(time, &enemy->getPrimaryCannon()));
                for (auto &externalCannon : dynamic_cast<Fighter &>(*(enemy)).getExternalCannons())
                    emplaceProjectile(dynamic_cast<Fighter &>(*enemy).useCannon(time, &externalCannon));
            } else if (typeid(*enemy) == typeid(Assaulter)) {
                dynamic_cast<Assaulter &>(*enemy).move(time);
                emplaceProjectile(dynamic_cast<Assaulter &>(*enemy).useCannon(
                        time, &enemy->getPrimaryCannon(), player->getSprite().getPosition()));
            }
        }
    }
}

void Game::updateAsteroids(float time) {
    for (auto asteroidIter = asteroidManager.begin(); asteroidIter != asteroidManager.end();) {
        (*asteroidIter)->getAnimator()->update(time);
        (*asteroidIter)->move(time);
        checkForAsteroidsCollisions(asteroidIter++);
    }
}

void Game::updateProjectiles(float time) {
    for (auto projectileIter = projectileManager.begin(); projectileIter != projectileManager.end();) {
        (*projectileIter)->move(time);
        checkForProjectileCollisions(projectileIter++);
    }
}

void Game::drawPowerUp() {
    if (powerUp != nullptr)
        window.draw(powerUp->getSprite());
}

void Game::drawProjectiles() {
    for (auto &i : projectileManager)
        window.draw(i->getSprite());
}

void Game::drawPlayer() {
    window.draw(player->getSprite());

    auto &playerType = *player; //todo reduce scope
    if (isUsingSpecial)
        if (typeid(playerType) == typeid(Raptor))
            window.draw(dynamic_cast<Raptor &>(*player).getShield());

    if (player->isLaserActive())
        window.draw(player->getLaser());
}

void Game::drawEnemies() {
    for (auto &i : enemyManager)
        window.draw(i->getSprite());
}

void Game::drawBackground() {
    window.draw(background->getSprite1());
    window.draw(background->getSprite2());
}

void Game::drawAsteroids() {
    for (auto &i : asteroidManager)
        window.draw(i->getSprite());
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

void Game::checkForProjectileCollisions(std::list<std::unique_ptr<Projectile>>::iterator projectileIter) {
    sf::Sprite &projSprite = (*projectileIter)->getSprite();
    if (isOutOfSigth(projSprite)) {
        projectileManager.erase(projectileIter);
        return;
    }

    if ((*projectileIter)->isEvil()) {
        auto &playerType = *player;
        if (typeid(playerType) == typeid(Raptor))
            if (isUsingSpecial && !player->isCharging()) {
                auto shield = dynamic_cast<Raptor &>(*player).getShield();
                if (dist(projSprite.getPosition(), shield.getPosition()) <=
                    (shield.getRadius() + projSprite.getGlobalBounds().height / 2)) {
                    projectileManager.erase(projectileIter);
                    return;
                }
            }

        if (player->getBoundingBox().getGlobalBounds().intersects((projSprite.getGlobalBounds()))) {
            player->receiveDamage((*projectileIter)->getDamage()); //todo handle death in one position
            projectileManager.erase(projectileIter);
            return;
        }
    } else { //todo bounding box, or circle collision if projectile is a circle
        for (auto asteroidIter = asteroidManager.begin(); asteroidIter != asteroidManager.end(); asteroidIter++) {
            if ((*asteroidIter)->getSprite().getGlobalBounds().intersects(projSprite.getGlobalBounds())) {
                asteroidManager.erase(asteroidIter);
                projectileManager.erase(projectileIter);
                return;
            }
        }
        for (auto &enemy : enemyManager) {
            if (enemy->getBoundingBox().getGlobalBounds().intersects((projSprite.getGlobalBounds()))) {
                enemy->receiveDamage((*projectileIter)->getDamage());
                projectileManager.erase(projectileIter);
                return;
            }
        }
    }
}

void Game::checkForAsteroidsCollisions(std::list<std::unique_ptr<Asteroid>>::iterator asteroidIter) {
    sf::Sprite &asteroidSprite = (*asteroidIter)->getSprite();
    if (isOutOfSigth(asteroidSprite)) {
        asteroidManager.erase(asteroidIter);
        return;
    }

    auto &playerType = *player;
    if (typeid(playerType) == typeid(Raptor))
        if (isUsingSpecial && !player->isCharging()) {
            auto shield = dynamic_cast<Raptor &>(*player).getShield();
            if (dist(asteroidSprite.getPosition(), shield.getPosition()) <=
                (shield.getRadius() + localRadius * (*asteroidIter)->getSize())) {
                asteroidManager.erase(asteroidIter);
                return;
            }
        }

    if (player->getBoundingBox().getGlobalBounds().intersects((asteroidSprite.getGlobalBounds()))) {
        player->receiveDamage((*asteroidIter)->getDamage());
        asteroidManager.erase(asteroidIter);
        return;
    }
}

void Game::checkForLaserCollision(float time) {
    for (auto &enemy : enemyManager) {
        if (enemy->getBoundingBox().getGlobalBounds().intersects((player->getLaser().getGlobalBounds()))) {
            enemy->receiveDamage(20.f * time);
        }
    }

    for (auto asteroidIter = asteroidManager.begin(); asteroidIter != asteroidManager.end(); asteroidIter++) {
        if ((*asteroidIter)->getSprite().getGlobalBounds().intersects(player->getLaser().getGlobalBounds())) {
            asteroidManager.erase(asteroidIter); //damage to asteroids
            break;
        }
    }
}

bool Game::isOutOfSigth(const sf::Sprite &sprite) const {
    return sprite.getPosition().y + sprite.getOrigin().y < 0 ||
           sprite.getPosition().y - sprite.getOrigin().y > windowHeight ||
           sprite.getPosition().x + sprite.getOrigin().x < 0 ||
           sprite.getPosition().x - sprite.getOrigin().x > windowWidth;
}

bool Game::isLegalMove(float x, float origin, short int direction) {
    return !((x <= origin && direction == left) || (x >= windowWidth - origin && direction == right));
}

float Game::dist(const sf::Vector2f &pointA, const sf::Vector2f &pointB) {
    return sqrt(pow(pointB.x - pointA.x, 2) + pow(pointB.y - pointA.y, 2));
}

void Game::emplaceProjectile(std::unique_ptr<Projectile> projectile) {
    if (projectile != nullptr)
        projectileManager.emplace_back(new Projectile(*projectile));
}
