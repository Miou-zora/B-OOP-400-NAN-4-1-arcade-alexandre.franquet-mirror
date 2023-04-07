/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** sdl2
*/

#pragma once
#include <ncurses.h>
#include <map>
#include "../core/src/Lib/ALib.hpp"

namespace Arcade {
    class NcursesDisplayModule : virtual public Arcade::ALib {
        /**
         *  @brief The class NcursesDisplayModule is the class that manages the display with the SDL2 library
         *  @details It can use the sprite throug a dict made of std::string -> sf::Sprite
         */

        public:
            NcursesDisplayModule(void);
            ~NcursesDisplayModule();

            void createWindow(void) override final;
            void closeWindow(void) override final;
            void clearWindow(void) override final;
            void renderWindow(void) override final;
            bool isWindowClosed(void);
            void updateEvent(void);
            void drawObjets(std::shared_ptr<Arcade::IObject> object);
            void drawShapes(Arcade::Shapes shape, Arcade::Colors color, std::pair<ssize_t, ssize_t> pos, std::pair<ssize_t, ssize_t> size);
            void drawText(std::shared_ptr<Arcade::Text> text);
            void drawText(std::string str, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> pos);

            bool isKeyPressed(Arcade::Inputs) override;
            bool isKeyReleased(Arcade::Inputs) override;

        private:
            bool _window;

            std::map<int/*ncurses input*/, Arcade::Inputs> _keyMap = {
                {'A', Arcade::IKEY_UP},
                {'B', Arcade::IKEY_RIGHT},
                {'C', Arcade::IKEY_RIGHT},
                {'D', Arcade::IKEY_LEFT},
                {'a', Arcade::IKEY_A},
                {'b', Arcade::IKEY_B},
                {'c', Arcade::IKEY_C},
                {'d', Arcade::IKEY_D},
                {'e', Arcade::IKEY_E},
                {'f', Arcade::IKEY_F},
                {'g', Arcade::IKEY_G},
                {'h', Arcade::IKEY_H},
                {'i', Arcade::IKEY_I},
                {'j', Arcade::IKEY_J},
                {'k', Arcade::IKEY_K},
                {'l', Arcade::IKEY_L},
                {'m', Arcade::IKEY_M},
                {'n', Arcade::IKEY_N},
                {'o', Arcade::IKEY_O},
                {'p', Arcade::IKEY_P},
                {'q', Arcade::IKEY_Q},
                {'r', Arcade::IKEY_R},
                {'s', Arcade::IKEY_S},
                {'t', Arcade::IKEY_T},
                {'u', Arcade::IKEY_U},
                {'v', Arcade::IKEY_V},
                {'w', Arcade::IKEY_W},
                {'x', Arcade::IKEY_X},
                {'y', Arcade::IKEY_Y},
                {'z', Arcade::IKEY_Z},
                {' ', Arcade::IKEY_SPACE},
                {'\n', Arcade::IKEY_ENTER},
                {'\t', Arcade::IKEY_TAB},
                {260, Arcade::IKEY_LEFT},
                {259, Arcade::IKEY_UP},
                {261, Arcade::IKEY_RIGHT},
                {258, Arcade::IKEY_DOWN}
            };
    };
}
