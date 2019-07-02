//
// Created by Fabio Luccioletti on 2019-07-02.
//

#include "Minion.h"
#include "ResourceManager.h"

Minion::Minion() : Enemy(50, 10, 100), elapsedTime(0) { //todo adjust values
    sprite.setTexture(ResourceManager::getTexture("../Texture/Minion.png"));
    sprite.setOrigin(106, 134);
    primaryCannon.setFireRate(250);
    primaryCannon.setNShots(1);
    primaryCannon.setTracker(false);
    primaryCannon.setSpaceshipPtr(this);
    Projectile projectilePrototype(sf::Vector2f(0.5, 0.5), 40, &primaryCannon, sf::Vector2f(0, 1), strength);
    primaryCannon.setProjectilePrototype(projectilePrototype);

}

void Minion::move(float time) {
    elapsedTime += time;
    if (elapsedTime < 1)
        sprite.move(speed * time, 0);
    else if (elapsedTime > 2)
        elapsedTime = 0;
}
