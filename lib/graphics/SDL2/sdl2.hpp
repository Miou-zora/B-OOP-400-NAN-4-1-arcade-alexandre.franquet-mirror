/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** sdl2
*/

#pragma once
#include <SDL2/SDL.h>
#include <map>
#include "../core/src/Lib/ALib.hpp"

namespace Arcade {
    class SdlDisplayModule : virtual public Arcade::ALib {
        /**
         *  @brief The class SdlDisplayModule is the class that manages the display with the SDL2 library
         *  @details It can use the sprite throug a dict made of std::string -> sf::Sprite
         */

        public:
            SdlDisplayModule(void);
            ~SdlDisplayModule();

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
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            // std::map<std::string, SDL_Surface> _textures;
            // std::map<std::string, SDL_Texture> _sprites;

            // SDL_Color arcadeColorToSfColor(Arcade::Colors color);
            // std::unique_ptr<SDL_S> arcadeShapeToSfShape(Arcade::Shapes shape, std::pair<ssize_t, ssize_t> size);

            // SDL_Event _event;
            // std::map<SDL_KeyCode, Arcade::Inputs> _keyMap = {
            //     {SDLK_LEFT, Arcade::Inputs::IKEY_LEFT},
            //     {SDLK_RIGHT, Arcade::Inputs::IKEY_RIGHT},
            //     {SDLK_UP, Arcade::Inputs::IKEY_UP},
            //     {SDLK_DOWN, Arcade::Inputs::IKEY_DOWN},
            //     {SDLK_SPACE, Arcade::Inputs::IKEY_SPACE},
            //     {SDLK_q, Arcade::Inputs::IKEY_Q},
            //     {SDLK_ESCAPE, Arcade::Inputs::IKEY_ESC},
            //     {SDLK_g, Arcade::Inputs::IKEY_G},
            //     {SDLK_h, Arcade::Inputs::IKEY_H},
            // };
    };
}
