//
// Created by Fabio Luccioletti on 2019-06-30.
//

#ifndef ASPACEGAME_RESOURCEMANAGER_H
#define ASPACEGAME_RESOURCEMANAGER_H


#include <SFML/Graphics.hpp>
#include <map>


class ResourceManager {
public:
    ResourceManager();

    static sf::Texture &getTexture(std::string const &filename);

private:
    std::map<std::string, sf::Texture> textures;

    static ResourceManager *sIstance;

};


#endif //ASPACEGAME_RESOURCEMANAGER_H
