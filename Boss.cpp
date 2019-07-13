//
// Created by gianmarco on 30/06/19.
//

#include "Boss.h"
#include "ResourceManager.h"
#include "Functions.h"

void Boss::move(float time) {
    elapsedTime += time;
    if (elapsedTime < bossSpawnDuration) {
        sprite.move(0, (bossFinalPosition - bossStartPosition) / bossSpawnDuration * time);
        //boundingBox.setScale(0,0); //todo invincible during spawn
    } else
        Enemy::move(time);
}

std::list<Cannon *> &Boss::chooseAttack() { //fixme
    int choice = getRandomInt(0, 2);
    switch (choice) {
        case 0:
            currentAttack.clear();
            currentAttack = simpleCannons;
            currentAttack.push_back(&primaryCannon);
            break;
        case 1:
            currentAttack.clear();
            currentAttack.push_back(mobileCannon);
            break;
        case 2:
            currentAttack.clear();
            currentAttack = bombCannon;
            currentAttack.push_back(trackerCannon);
            break;
        default:
            break;
    }
    return currentAttack;
}

Boss::Boss() : Enemy(1000.f, 10.f, 50.f, 1.f, Cannon(Projectile(400, 10.f * 1)), 15) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Boss.png"));
    sprite.setScale(0.5, 0.4);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    bossStartPosition = -sprite.getScale().y * sprite.getOrigin().y;
    bossFinalPosition = sprite.getScale().y * sprite.getOrigin().y + bossSpawnHeight;

    sprite.setPosition(static_cast<float>(windowWidth) / 2, bossStartPosition);

    boundingBox.setSize(sf::Vector2f(1.6f * sprite.getOrigin().x,
                                     1.4f * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
    simpleCannons.emplace_back(new Cannon(primaryCannon));
    simpleCannons.back()->setLocalRelativePosition(sf::Vector2f(-250, 0));
    simpleCannons.emplace_back(new Cannon(primaryCannon));
    simpleCannons.back()->setLocalRelativePosition(sf::Vector2f(250, 0));
    bombCannon.emplace_back(
            new Cannon(Projectile(400, strength * 3, true, sf::Vector2f(0.9, 0.9)), 1, 3, false,
                       sf::Vector2f(-250, 0)));
    bombCannon.emplace_back(
            new Cannon(Projectile(400, strength * 3, true, sf::Vector2f(0.9, 0.9)), 1, 3, false, sf::Vector2f(250, 0)));
    mobileCannon = new Cannon(primaryCannon);
    mobileCannon->setFireRateMultiplier(5);
    mobileCannon->setElapsedTime(0);
    trackerCannon = new Cannon(Projectile(300, strength * 2), 1, 2, true);
}

std::unique_ptr<Projectile> Boss::useCannon(float dt, Cannon &cannon, const sf::Vector2f &playerPos) {
    sf::Vector2f vector(playerPos - sprite.getPosition());
    float module = hypot(vector.x, vector.y);
    cannon.getProjectilePrototype().setMovement(sf::Vector2f(vector.x / module, vector.y / module));
    return Spaceship::useCannon(dt, cannon);
}

std::unique_ptr<Projectile> Boss::useMobileCannon(float dt, Cannon &cannon) {
    mobileTime += dt;
    if (mobileTime <= 5) {
        angle += (((M_PI / 2) / 5) * dt);
        sf::Vector2f movement(cos(angle), sin(angle));
        cannon.getProjectilePrototype().setMovement(movement);
    } else if (mobileTime > 5 && mobileTime < 2 * 5) {
        angle -= (((M_PI / 2) / 5) * dt);
        sf::Vector2f movement(cos(angle), sin(angle));
        cannon.getProjectilePrototype().setMovement(movement);
    } else {
        mobileTime = 0;
        angle = M_PI / 4;
    }
    return Spaceship::useCannon(dt, cannon);
}

std::unique_ptr<Projectile> Boss::useCannon(float dt, Cannon &cannon) {
    return Spaceship::useCannon(dt, cannon);
}

Boss::~Boss() {
    delete mobileCannon;
    delete trackerCannon;
    for (auto &i:simpleCannons)
        delete i;
    for (auto &i:bombCannon)
        delete i;
}
