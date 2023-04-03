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
            SfmlLib(void) = default;
            ~SfmlLib();
            bool isWindowClosed(void);
            void updateEvent(void);
            void createWindow(void);
            void closeWindow(void);
            void clearWindow(void);
            void renderWindow(void);
            void drawObjets(std::shared_ptr<Arcade::IObject> object);
            void drawShapes(Arcade::Shapes shape, Arcade::Colors color, std::pair<ssize_t, ssize_t> pos, std::pair<ssize_t, ssize_t> size);
            void drawText(std::shared_ptr<Arcade::Text> text);
            void drawText(std::string str, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> pos);

        private:

            sf::Color arcadeColorToSfColor(Arcade::Colors color);
            std::unique_ptr<sf::Shape> arcadeShapeToSfShape(Arcade::Shapes shape, std::pair<ssize_t, ssize_t> size);

            sf::RenderWindow _window;
            std::map<std::string, sf::Texture> _textures;
            std::map<std::string, sf::Sprite> _sprites;
            sf::Event _event;
            std::map<std::string, sf::Font> _fonts;
            std::map<std::string, sf::Text> _texts;
            std::map<sf::Keyboard::Key, Arcade::Inputs> _keyMap = {
                {sf::Keyboard::Key::Left, Arcade::Inputs::KEY_LEFT},
                {sf::Keyboard::Key::Right, Arcade::Inputs::KEY_RIGHT},
                {sf::Keyboard::Key::Up, Arcade::Inputs::KEY_UP},
                {sf::Keyboard::Key::Down, Arcade::Inputs::KEY_DOWN},
                {sf::Keyboard::Key::Space, Arcade::Inputs::KEY_SPACE},
                {sf::Keyboard::Key::Q, Arcade::Inputs::KEY_Q},
                {sf::Keyboard::Key::Escape, Arcade::Inputs::KEY_ESC},
                {sf::Keyboard::Key::G, Arcade::Inputs::KEY_G},
                {sf::Keyboard::Key::H, Arcade::Inputs::KEY_H},
            };
    };
}
