/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** sfml
*/

#pragma once
#include <SFML>
#include "ADisplay.hpp"
#include "IObject.hpp"

namespace Arcade {
    class SfmlDisplay : virtual public Arcade::ADisplay {

        /**
         *  @brief The class SfmlDisplay is the class that manages the display with the SFML library
         *  @details It can use the sprite throug a dict made of std::string -> sf::Sprite
         */

        public:
            SfmlDisplay(void) final;
            ~SfmlDisplay() override final;

            void createWindow(void) override final;
            void closeWindow(void) override final;
            void clearWindow(void) override final;
            void renderWindow(void) override final;
            void drawObjets(Arcade::IObjets) override final;
            void drawText(Arcade::Text) {} override final;
            unsigned int setScale(void) {} override final;
            unsigned int setPosition(void) {} override final;

        private:
            sf::RenderWindow _window;
            std::map<std::string, sf::Texture> _textures;
            std::map<std::string, sf::Sprite> _sprites;
    }
}