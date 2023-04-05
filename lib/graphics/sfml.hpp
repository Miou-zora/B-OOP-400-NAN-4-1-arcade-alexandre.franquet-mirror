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

            bool isKeyPressed(Arcade::Inputs) override;
            bool isKeyReleased(Arcade::Inputs) override;

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
                {sf::Keyboard::Key::Left, Arcade::Inputs::IKEY_LEFT},
                {sf::Keyboard::Key::Right, Arcade::Inputs::IKEY_RIGHT},
                {sf::Keyboard::Key::Up, Arcade::Inputs::IKEY_UP},
                {sf::Keyboard::Key::Down, Arcade::Inputs::IKEY_DOWN},
                {sf::Keyboard::Key::Space, Arcade::Inputs::IKEY_SPACE},
                {sf::Keyboard::Key::Escape, Arcade::Inputs::IKEY_ESC},
                {sf::Keyboard::Key::Return, Arcade::Inputs::IKEY_ENTER},
                {sf::Keyboard::Key::BackSpace, Arcade::Inputs::IKEY_BACKSPACE},
                {sf::Keyboard::Key::Tab, Arcade::Inputs::IKEY_TAB},
                {sf::Keyboard::Key::LShift, Arcade::Inputs::IKEY_SHIFT},
                {sf::Keyboard::Key::LControl, Arcade::Inputs::IKEY_CTRL},
                {sf::Keyboard::Key::LAlt, Arcade::Inputs::IKEY_ALT},
                {sf::Keyboard::Key::B, Arcade::Inputs::IKEY_B},
                {sf::Keyboard::Key::D, Arcade::Inputs::IKEY_D},
                {sf::Keyboard::Key::S, Arcade::Inputs::IKEY_S},
                {sf::Keyboard::Key::M, Arcade::Inputs::IKEY_M},
                {sf::Keyboard::Key::Q, Arcade::Inputs::IKEY_Q},
                {sf::Keyboard::Key::A, Arcade::Inputs::IKEY_A},
                {sf::Keyboard::Key::C, Arcade::Inputs::IKEY_C},
                {sf::Keyboard::Key::E, Arcade::Inputs::IKEY_E},
                {sf::Keyboard::Key::F, Arcade::Inputs::IKEY_F},
                {sf::Keyboard::Key::G, Arcade::Inputs::IKEY_G},
                {sf::Keyboard::Key::H, Arcade::Inputs::IKEY_H},
                {sf::Keyboard::Key::I, Arcade::Inputs::IKEY_I},
                {sf::Keyboard::Key::J, Arcade::Inputs::IKEY_J},
                {sf::Keyboard::Key::K, Arcade::Inputs::IKEY_K},
                {sf::Keyboard::Key::L, Arcade::Inputs::IKEY_L},
                {sf::Keyboard::Key::N, Arcade::Inputs::IKEY_N},
                {sf::Keyboard::Key::O, Arcade::Inputs::IKEY_O},
                {sf::Keyboard::Key::P, Arcade::Inputs::IKEY_P},
                {sf::Keyboard::Key::R, Arcade::Inputs::IKEY_R},
                {sf::Keyboard::Key::T, Arcade::Inputs::IKEY_T},
                {sf::Keyboard::Key::U, Arcade::Inputs::IKEY_U},
                {sf::Keyboard::Key::V, Arcade::Inputs::IKEY_V},
                {sf::Keyboard::Key::W, Arcade::Inputs::IKEY_W},
                {sf::Keyboard::Key::X, Arcade::Inputs::IKEY_X},
                {sf::Keyboard::Key::Y, Arcade::Inputs::IKEY_Y},
                {sf::Keyboard::Key::Z, Arcade::Inputs::IKEY_Z},
           };
    };
}
