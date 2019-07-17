//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include <iostream>
#include <fstream>
#include "Game.h"
#include "ResourceManager.h"
#include "Raptor.h"
#include "Kamikaze.h"
#include "Bomber.h"
#include <cmath>
#include <fstream>

Game::Game() : window(sf::VideoMode(static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)),
                      "A Space Game"), isPaused(false), isMovingLeft(false), isMovingRight(false), isShooting(false),
               isChoosingPlayer(true),
               isUsingSpecial(false), view((sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))),
               achievement(&entityManager) {

    createHud();

    achievement.attach();
    achievementDuration = 0;
    achievementSound.setBuffer(ResourceManager::getSoundBuffer("../sound/achievement.wav"));
    achievementSound.setVolume(50);
    key.setBuffer(ResourceManager::getSoundBuffer("../sound/key.wav"));
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
    text.setString("Choose your player");
    playerSelection = text;
    playerSelection.setOrigin(playerSelection.getLocalBounds().width / 2, playerSelection.getLocalBounds().height / 2);
    playerSelection.setPosition(windowWidth / 2, windowHeight / 6);
    playerSelection.setFillColor(sf::Color::White);
    playerSelection.setOutlineThickness(1);
    playerSelection.setOutlineColor(sf::Color::Blue);
    text.setString("A: Bomber                         S: Raptor");
    playerNames = text;
    playerNames.setOrigin(playerNames.getLocalBounds().width / 2, playerNames.getLocalBounds().height / 2);
    playerNames.setPosition(windowWidth / 2, playerSelection.getPosition().y + 50);
    playerNames.setFillColor(sf::Color::White);
    playerNames.setOutlineThickness(1);
    playerNames.setOutlineColor(sf::Color::Blue);
    text.setString("Game Over");
    gameOver = text;
    gameOver.setFillColor(sf::Color::White);
    gameOver.setCharacterSize(90);
    gameOver.setPosition(175, 250);
    gameOver.setOutlineThickness(2);
    gameOver.setOutlineColor(sf::Color::Blue);

    readFile();

    leadboardTitle.setFont(ResourceManager::getFont("../font/font.ttf"));
    leadboardTitle.setString("Leadboard:");
    leadboardTitle.setCharacterSize(22);
    leadboardTitle.setFillColor(sf::Color::White);
    leadboardTitle.setOutlineThickness(0.5);
    leadboardTitle.setOutlineColor(sf::Color::Yellow);
    leadboardTitle.setOrigin(leadboardTitle.getLocalBounds().width / 2, 0);
    leadboardTitle.setPosition(windowWidth / 2, 375);


    leadboard.setFont(ResourceManager::getFont("../font/font.ttf"));
    leadboard.setOrigin(leadboard.getGlobalBounds().width / 2, 0);
    leadboard.setFillColor(sf::Color::White);
    leadboard.setCharacterSize(22);
    leadboard.setOutlineThickness(0.5);
    leadboard.setOutlineColor(sf::Color::Yellow);
    leadboard.setPosition(leadboardTitle.getPosition().x - 50, leadboardTitle.getPosition().y + 50);

    insertScore.setFont(ResourceManager::getFont("../font/font.ttf"));
    insertScore.setFillColor(sf::Color::White);
    insertScore.setOutlineThickness(1);
    insertScore.setOutlineColor(sf::Color::Blue);
    insertScore.setPosition(200, 100);

    bomberSprite.setTexture(ResourceManager::getTexture("../Texture/BomberBasic.png"));
    bomberSprite.setScale(maxScale, maxScale);
    bomberSprite.setOrigin(bomberSprite.getLocalBounds().width / 2, 0);
    bomberSprite.setPosition(playerSelection.getGlobalBounds().left, 200);
    raptorSprite.setTexture(ResourceManager::getTexture("../Texture/RaptorBasic.png"));
    raptorSprite.setScale(maxScale, maxScale);
    raptorSprite.setOrigin(raptorSprite.getLocalBounds().width / 2, 0);
    raptorSprite.setPosition(playerSelection.getGlobalBounds().left + playerSelection.getGlobalBounds().width, 200);

    nameText.setPosition(insertScore.getPosition().x + 340, insertScore.getPosition().y + 72);
    nameText.setFillColor(sf::Color::White);
    nameText.setOutlineThickness(1);
    nameText.setOutlineColor(sf::Color::Blue);
    nameText.setFont(ResourceManager::getFont("../font/font.ttf"));
}

void Game::run() {
    sf::Clock clock;
    sf::Time deltaTime;
    while (window.isOpen()) {
        deltaTime = clock.restart();
        processEvents();
        if (!isPaused && !isChoosingPlayer && !entityManager.isGameEnded())
            update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (entityManager.isGameEnded() && entityManager.getGameOver().getStatus() == sf::Sound::Stopped) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Enter && !nameEntered) {
                        key.play();
                        insertScoreName();
                        nameEntered = true;
                    } else if (event.key.code == sf::Keyboard::BackSpace && !nameEntered) {
                        key.play();
                        std::string name = nameText.getString();
                        name = name.substr(0, std::max(static_cast<unsigned long>(0), name.length() - 1));
                        nameText.setString(name);
                    }
                    break;
                case sf::Event::TextEntered:
                    if (nameText.getString().getSize() < 10 && !nameEntered && event.text.unicode != 8) {
                        key.play();
                        nameText.setString(nameText.getString() + (sf::String(event.text.unicode)));
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        } else {
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
}

void Game::update(const sf::Time &dt) {

    float time = dt.asSeconds();
    entityManager.updateSpawn(time);
    entityManager.updateAsteroids(time, isUsingSpecial);
    entityManager.updateEnemies(time);
    entityManager.updatePlayer(time, isMovingRight, isMovingLeft, isShooting, isUsingSpecial, specialHud, hpHud);
    entityManager.updateProjectiles(time, isUsingSpecial);
    entityManager.updatePowerUp(time, hpHud, specialHud);

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
    if (!isChoosingPlayer && !entityManager.isGameEnded()) {
        draw<Asteroid>(entityManager.getAsteroidManager());
        draw<Projectile>(entityManager.getProjectileManager());
        drawEnemy();
        drawPlayer();
        drawPowerUp();
        drawHud();
        drawAchievement();
    } else if (isChoosingPlayer) {
        window.draw(playerSelection);
        window.draw(playerNames);
        window.draw(bomberSprite);
        window.draw(raptorSprite);
        window.draw(leadboardTitle);
        window.draw(leadboard);
    } else if (entityManager.isGameEnded()) {
        if (entityManager.getGameOver().getStatus() == sf::Sound::Playing)
            window.draw(gameOver);
        else {
            insertScore.setString(std::string("Your Score:  ") + std::to_string(entityManager.getScore()) +
                                  std::string("\n\nInsert name:    "));
            window.draw(insertScore);
            window.draw(nameText);
            if (nameEntered) {
                window.draw(leadboardTitle);
                window.draw(leadboard);
            }
        }
    }

    window.display();
}

void Game::drawAchievement() {
    if (!achievementSprites.empty())
        window.draw(*achievementSprites.front());
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

    if (player->getHp() <= 0)
        for (auto &explosion : player->getExplosions())
            window.draw(explosion);
    else {
        if (isUsingSpecial && player->isMovable()) {
            auto &playerType = *(player.get());
            if (typeid(playerType) == typeid(Raptor))
                window.draw(dynamic_cast<Raptor &>(playerType).getShield());
        }

        if (player->isLaserActive())
            window.draw(player->getLaser());
    }
}

void Game::drawEnemy() {
    for (auto &enemy: entityManager.getEnemyManager()) {

        auto &enemyType = *(enemy.get());
        window.draw(enemy->getSprite());
        if (enemy->getHp() <= 0)
            for (auto &explosion : enemy->getExplosions())
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

bool Game::isLegalMove(float x, float origin, short int direction) {
    return !((x <= origin && direction == left) || (x >= windowWidth - origin && direction == right));
}

void Game::updateAchievement(float time) {
    if (!achievement.getSprites().empty()) {
        for (auto &sprite : achievement.getSprites()) {
            achievementSprites.emplace_back(new sf::Sprite(sprite));
        }
        achievement.getSprites().clear();
    }
    if (!achievementSprites.empty()) {
        if (achievementDuration == 0) {
            achievementSound.play();
        }
        achievementDuration += time;
        if (achievementDuration <= achievementFadeDuration)
            achievementSprites.front()->setColor(sf::Color(255, 255, 255, std::min(static_cast<int>(
                                                                                           255. /
                                                                                           achievementFadeDuration *
                                                                                           achievementDuration), 255)));
        else if (achievementDuration >= achievementDisappearT - achievementFadeDuration &&
                 achievementDuration < achievementDisappearT)
            achievementSprites.front()->setColor(sf::Color(255, 255, 255, std::max(0, static_cast<int>(
                    255. / achievementFadeDuration * (achievementDisappearT - achievementDuration)))));
        else if (achievementDuration > achievementAnimationT) {
            achievementSprites.pop_front();
            achievementDuration = 0;
            if (!achievementSprites.empty())
                achievementSprites.front()->setColor(sf::Color(255, 255, 255, 0));
        }
    }
}

void Game::insertScoreName() {
    std::ifstream iFile("../leadboard.txt");
    char fileText[50];
    std::vector<std::pair<int, std::string>> scoresVect;
    int i = 0;
    int score = 0;
    std::string name;
    while (i < 10 && !iFile.eof()) {
        iFile.getline(fileText, 50);
        if (i % 2 != 0) {
            score = std::stoi(fileText);
            scoresVect.emplace_back(score, name);
        }
        if (i % 2 == 0) {
            name = fileText;
        }
        i++;
    }
    iFile.close();
    scoresVect.emplace_back(entityManager.getScore(), nameText.getString() + std::string(": "));
    std::sort(scoresVect.begin(), scoresVect.end());
    std::ofstream oFile;
    oFile.open("../leadboard.txt", std::ofstream::out | std::ofstream::trunc);
    i = 5;
    bool arrow = false;
    leadboard.setString("");
    leadboard.setPosition(insertScore.getPosition().x + 205, leadboardTitle.getPosition().y + 50);
    while (i > 0 && !oFile.eof()) {
        oFile.write(scoresVect[i].second.data(), scoresVect[i].second.length());
        if (scoresVect[i].second != std::string("defaultvalue:"))
            leadboard.setString(leadboard.getString() + scoresVect[i].second + std::string(" "));
        oFile.write("\n", 1);
        oFile.write(std::to_string(scoresVect[i].first).data(), std::to_string(scoresVect[i].first).length());
        if (scoresVect[i].second == nameText.getString() + std::string(": ") &&
            scoresVect[i].first == entityManager.getScore() && !arrow) {
            leadboard.setString(
                    leadboard.getString() + std::to_string(scoresVect[i].first) + std::string("        <---") +
                    std::string("\n"));
            arrow = true;
        }
        else if (scoresVect[i].second != std::string("defaultvalue:"))
            leadboard.setString(leadboard.getString() + std::to_string(scoresVect[i].first) + std::string("\n"));
        oFile.write("\n", 1);
        i--;
    }
    oFile.close();
}

void Game::readFile() {
    std::ifstream openFile("../leadboard.txt");
    char fileText[100];
    std::string fileComplete;
    int i = 0;
    bool zero = false;
    while (i < 10 && !openFile.eof()) {
        openFile.getline(fileText, 100);
        if (i % 2 == 0) {
            if (fileText == std::string("defaultvalue:")) {
                zero = true;
            } else {
                fileComplete += (fileText + std::string(" "));
            }
        }
        if (i % 2 != 0) {
            if (zero) {
                zero = false;
            } else {
                fileComplete += (fileText);
                fileComplete += "\n";
            }
        }
        i++;
    }
    leadboard.setString(fileComplete);
    openFile.close();
}
