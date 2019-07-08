//
// Created by Fabio Luccioletti on 2019-06-30.
//

#ifndef ASPACEGAME_RESOURCEMANAGER_H
#define ASPACEGAME_RESOURCEMANAGER_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>


class ResourceManager {
public:
    ResourceManager();

    static sf::Texture &getTexture(std::string const &filename);

    static sf::SoundBuffer &getSoundBuffer(std::string const &filename);

    static sf::Font &getFont(std::string const &filename);


private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Font> fonts;


    static ResourceManager *sIstance;

};


#endif //ASPACEGAME_RESOURCEMANAGER_H
