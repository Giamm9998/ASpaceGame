//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include <cassert>
#include "ResourceManager.h"
#include <iostream>

ResourceManager *ResourceManager::sInstance = nullptr;

ResourceManager::ResourceManager() {
    assert(sInstance == nullptr); //ResourceManager is a Singleton
    sInstance = this;
}

sf::Texture &ResourceManager::getTexture(std::string const &filename) {
    auto &texMap = sInstance->textures;

    auto pairFound = texMap.find(filename);

    if (pairFound != texMap.end()) {
        return pairFound->second;
    } else {
        auto &texture = texMap[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}

sf::SoundBuffer &ResourceManager::getSoundBuffer(std::string const &filename) {
    auto &soundMap = sInstance->soundBuffers;

    auto pairFound = soundMap.find(filename);

    if (pairFound != soundMap.end()) {
        return pairFound->second;
    } else {
        auto &soundBuffer = soundMap[filename];
        soundBuffer.loadFromFile(filename);
        return soundBuffer;
    }
}

sf::Font &ResourceManager::getFont(std::string const &filename) {
    auto &fontMap = sInstance->fonts;

    auto pairFound = fontMap.find(filename);

    if (pairFound != fontMap.end()) {
        return pairFound->second;
    } else {
        auto &font = fontMap[filename];
        font.loadFromFile(filename);
        return font;
    }
}
