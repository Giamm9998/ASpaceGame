//
// Created by Fabio Luccioletti on 2019-07-03.
//

#include "Animator.h"
#include "ResourceManager.h"

Animator::Animator(sf::Sprite &sprite) : sprite(sprite), currentTime(), currentAnimation(nullptr) {}

Animator::Animation &Animator::createAnimation(std::string const &name, std::string const &textureName,
                                               sf::Time const duration, bool loop) {

    animations.emplace_back(Animator::Animation(name, textureName, duration, loop));

    if (currentAnimation == nullptr)
        switchAnimation(&animations.back());

    return animations.back();
}

void Animator::switchAnimation(Animator::Animation *animation) {

    if (animation != nullptr) {
        sprite.setTexture(ResourceManager::getTexture(animation->animTextureName));
    }

    currentAnimation = animation;
    currentTime = sf::Time::Zero.asSeconds();

}

bool Animator::switchAnimation(std::string const &name) {

    auto animation = findAnimation(name);
    if (animation != nullptr) {
        switchAnimation(animation);
        return true;
    }
    return false;
}

Animator::Animation *Animator::findAnimation(std::string const &name) {

    for (auto &animation : animations) {
        if (animation.animName == name)
            return &animation;
    }
    return nullptr;
}

std::string Animator::getCurrentAnimationName() const {
    if (currentAnimation != nullptr)
        return currentAnimation->animName;
    return "";
}

void Animator::update(float const &time) {

    if (currentAnimation == nullptr || time < 0)
        return;

    currentTime += time;

    float scaledTime = (currentTime / currentAnimation->animDuration.asSeconds());
    unsigned long numFrames = currentAnimation->animFrames.size();
    int currentFrame = static_cast<int>(scaledTime * numFrames);

    if (currentAnimation->animLooping)
        currentFrame %= numFrames;
    else if (currentFrame >= numFrames)
        currentFrame = numFrames - 1;

    sprite.setTextureRect(currentAnimation->animFrames[currentFrame]);
}

Animator::~Animator() = default;
