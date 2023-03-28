/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** sdl2
*/

#pragma once
#include <SDL>
#include "ADisplay.hpp"
#include "IObject.hpp"

namespace Arcade {
    class SdlDisplayModule : public virtual ADisplay {
        /**
         *  @brief The class SdlDisplayModule is the class that manages the display with the SDL2 library
         *  @details It can use the sprite throug a dict made of std::string -> sf::Sprite
         */

        public:
            SdlDisplayModule(void) final;
            ~SdlDisplayModule() override final;

            void createWindow(void) override final;
            void closeWindow(void) override final;
            void clearWindow(void) override final;
            void renderWindow(void) override final;
            void drawObjets(Arcade::IObjets) override final;
            void drawText(Arcade::Text) {} override final;
            unsigned int setScale(void) {} override final;
            unsigned int setPosition(void) {} override final;

        private:
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            std::map<std::string, SDL_Surface> _textures;
            std::map<std::string, SDL_Textures> _sprites;
    }
}