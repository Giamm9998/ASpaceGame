//
// Created by Fabio Luccioletti on 2019-06-30.
//

#include "ResourceManager.h"
#include <cassert>

ResourceManager *ResourceManager::sIstance = nullptr;

ResourceManager::ResourceManager() {
    assert(sIstance == nullptr); //ResourceManager is a Singleton
    sIstance = this;
}

sf::Texture &ResourceManager::getTexture(std::string const &filename) {
    auto &texMap = sIstance->textures;

    auto pairFound = texMap.find(filename);

    if (pairFound != texMap.end()) {
        return pairFound->second;
    } else {
        auto &texture = texMap[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}