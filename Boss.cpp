//
// Created by gianmarco on 30/06/19.
//

#include "Boss.h"
#include "ResourceManager.h"

void Boss::move(float time) {
    elapsedTime += time;
    if (elapsedTime < bossSpawnDuration) {
        sprite.move(0, (bossFinalPosition - bossStartPosition) / bossSpawnDuration * time);
        //boundingBox.setScale(0,0); //todo invincible during spawn
    } else
        Enemy::move(time);
}

void Boss::chooseAttack() {

}

Boss::Boss() : Enemy(1000.f, 10.f, 50.f, 1.f, Cannon(Projectile(400, strength * 1)), 15) {
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
    simpleCannons.emplace_back(Cannon(primaryCannon));
    simpleCannons.back().setLocalRelativePosition(sf::Vector2f(-250, 0));
    simpleCannons.emplace_back(Cannon(primaryCannon));
    simpleCannons.back().setLocalRelativePosition(sf::Vector2f(250, 0));
    bombcannon.emplace_back(
            Cannon(Projectile(400, strength * 3, true, sf::Vector2f(0.9, 0.9)), 1, 3, false, sf::Vector2f(-250, 0)));
    bombcannon.emplace_back(
            Cannon(Projectile(400, strength * 3, true, sf::Vector2f(0.9, 0.9)), 1, 3, false, sf::Vector2f(250, 0)));
    mobileCannon = Cannon(primaryCannon);
    mobileCannon.setElapsedTime(0);
    trackerCannon = Cannon(Projectile(300, strength * 2), 1, 2, true);
}

std::list<Cannon> &Boss::getSimpleCannons() {
    return simpleCannons;
}

Cannon &Boss::getMobileCannon() {
    return mobileCannon;
}

Cannon &Boss::getTrackerCannon() {
    return trackerCannon;
}

std::list<Cannon> &Boss::getBombcannon() {
    return bombcannon;
}

std::unique_ptr<Projectile> Boss::useCannon(float dt, Cannon &cannon, const sf::Vector2f &playerPos) {
    sf::Vector2f vector(playerPos - sprite.getPosition());
    float module = hypot(vector.x, vector.y);
    trackerCannon.getProjectilePrototype().setMovement(sf::Vector2f(vector.x / module, vector.y / module));
    return Spaceship::useCannon(dt, cannon);
}

std::unique_ptr<Projectile> Boss::useCannon(float dt, Cannon &cannon) {
    mobileCannon.setElapsedTime(mobileCannon.getElapsedTime() + dt);
    if (mobileCannon.getElapsedTime() < 5) {
        angle += (((M_PI / 2) / 5) * dt);
        sf::Vector2f movement(cos(angle), sin(angle));
        mobileCannon.getProjectilePrototype().setMovement(movement);
    } else {
        mobileCannon.setElapsedTime(0);
        angle = M_PI / 4;
    }
    return Spaceship::useCannon(dt, cannon);
}
