/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** SfmlLib
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "../core/src/Lib/ALib.hpp"

namespace Arcade {
    class SfmlLib : virtual public Arcade::ALib {

        /**
         *  @brief The class SfmlDisplay is the class that manages the display with the SFML library
         *  @details It can use the sprite throug a dict made of std::string -> sf::Sprite
         */

        public:
            SfmlLib(void);
            ~SfmlLib();

            

        private:
            sf::RenderWindow _window;
            std::map<std::string, sf::Texture> _textures;
            std::map<std::string, sf::Sprite> _sprites;
    };
}
