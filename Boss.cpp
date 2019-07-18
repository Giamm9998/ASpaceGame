//
// Created by gianmarco on 30/06/19.
//

#include "Boss.h"
#include "ResourceManager.h"
#include "Functions.h"
#include "Game.h"

void Boss::move(float time) {
    elapsedTime += time;
    if (elapsedTime < 0) {
        sprite.move(0, (bossFinalPosition - bossStartPosition) / bossSpawnDuration * time);
        boundingBox.setPosition(sprite.getPosition());
    } else
        Enemy::move(time);
}

std::list<Cannon *> &Boss::chooseAttack() {
    int choice = getRandomInt(0, 2);
    switch (choice) {
        case 0:
            currentAttack.clear();
            for (auto &cannon : simpleCannons)
                currentAttack.push_back(&cannon);
            currentAttack.push_back(&primaryCannon);
            break;
        case 1:
            currentAttack.clear();
            currentAttack.push_back(&mobileCannon);
            break;
        case 2:
            currentAttack.clear();
            for (auto &cannon: bombCannon)
                currentAttack.push_back(&cannon);
            currentAttack.push_back(&trackerCannon);
            break;
        default:
            break;
    }
    return currentAttack;
}

Boss::Boss() : Enemy(bossHp, bossStrength, bossSpeed, bossFireRate,
                     Cannon(Projectile(bossProjectileSpeed, bossStrength * bossStrengthMult)), bossExplosions) {
    sprite.setTexture(ResourceManager::getTexture("../Texture/Boss.png"));
    sprite.setScale(bossScaleX, bossScaleY);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    bossStartPosition = -sprite.getScale().y * sprite.getOrigin().y;
    bossFinalPosition = sprite.getScale().y * sprite.getOrigin().y + bossSpawnHeight;

    sprite.setPosition(windowWidth / 2, bossStartPosition);

    boundingBox.setSize(sf::Vector2f(bossBoxSizeX * sprite.getOrigin().x,
                                     bossBoxSizeY * sprite.getOrigin().y));
    boundingBox.setScale(sprite.getScale());
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);
    boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
    simpleCannons.emplace_back(Cannon(primaryCannon));
    simpleCannons.back().setLocalRelativePosition(sf::Vector2f(-bossCannonRelativePosX, 0));
    simpleCannons.emplace_back(Cannon(primaryCannon));
    simpleCannons.back().setLocalRelativePosition(sf::Vector2f(bossCannonRelativePosX, 0));
    bombCannon.emplace_back(Cannon(Projectile(bossProjectileSpeed, bossStrength * bossBombStrengthMult, true,
                                              sf::Vector2f(0.9, 0.9)), 1, bossBombStrengthMult, false,
                                   sf::Vector2f(-bossCannonRelativePosX, 0)));
    bombCannon.emplace_back(Cannon(Projectile(bossProjectileSpeed, bossStrength * bossBombStrengthMult, true,
                                              sf::Vector2f(0.9, 0.9)), 1, bossBombStrengthMult, false,
                                   sf::Vector2f(bossCannonRelativePosX, 0)));
    mobileCannon = Cannon(Projectile(300, bossStrength * bossStrengthMult), bossMobileFireRateMult);
    mobileCannon.setElapsedTime(0);
    trackerCannon = Cannon(Projectile(300, bossStrength * bossTrackerStrengthMult), 1, bossTrackerStrengthMult, true);
    elapsedTime = -bossSpawnDuration;
}

std::unique_ptr<Projectile> Boss::useCannon(float dt, Cannon &cannon, const sf::Vector2f &playerPos) {
    sf::Vector2f vector(playerPos - (sprite.getPosition() + sf::Vector2f(0, sprite.getGlobalBounds().height / 2)));
    float module = hypot(vector.x, vector.y);
    cannon.getProjectilePrototype().setMovement(sf::Vector2f(vector.x / module, vector.y / module));
    return Spaceship::useCannon(dt, cannon);
}

std::unique_ptr<Projectile> Boss::useMobileCannon(float dt, Cannon &cannon) {
    mobileTime += dt;
    if (mobileTime <= bossMobileAttackDuration) {
        angle += (((M_PI / 2) / bossMobileAttackDuration) * dt);
        sf::Vector2f movement(static_cast<float>(cos(angle)), static_cast<float>(sin(angle)));
        cannon.getProjectilePrototype().setMovement(movement);
    } else if (mobileTime > bossMobileAttackDuration && mobileTime < 2 * bossMobileAttackDuration) {
        angle -= (((M_PI / 2) / bossMobileAttackDuration) * dt);
        sf::Vector2f movement(static_cast<float>(cos(angle)), static_cast<float>(sin(angle)));
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

Boss::~Boss() = default;
