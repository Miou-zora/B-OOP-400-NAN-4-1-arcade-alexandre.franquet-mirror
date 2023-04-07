/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** sdl2
*/

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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
            TTF_Font *_font;
            SDL_Surface *_surface;
            // std::map<std::string, SDL_Surface> _textures;
            // std::map<std::string, SDL_Texture> _sprites;

            SDL_Color arcadeColorToSfColor(Arcade::Colors color);
            // std::unique_ptr<SDL_S> arcadeShapeToSfShape(Arcade::Shapes shape, std::pair<ssize_t, ssize_t> size);

            std::map<SDL_Keycode, Arcade::Inputs> _keyMap = {
                {SDLK_LEFT, Arcade::Inputs::IKEY_LEFT},
                {SDLK_RIGHT, Arcade::Inputs::IKEY_RIGHT},
                {SDLK_UP, Arcade::Inputs::IKEY_UP},
                {SDLK_DOWN, Arcade::Inputs::IKEY_DOWN},
                {SDLK_SPACE, Arcade::Inputs::IKEY_SPACE},
                {SDLK_ESCAPE, Arcade::Inputs::IKEY_ESC},
                {SDLK_RETURN, Arcade::Inputs::IKEY_ENTER},
                {SDLK_BACKSPACE, Arcade::Inputs::IKEY_BACKSPACE},
                {SDLK_TAB, Arcade::Inputs::IKEY_TAB},
                {SDLK_LSHIFT, Arcade::Inputs::IKEY_SHIFT},
                {SDLK_LCTRL, Arcade::Inputs::IKEY_CTRL},
                {SDLK_LALT, Arcade::Inputs::IKEY_ALT},
                {SDLK_a, Arcade::Inputs::IKEY_A},
                {SDLK_b, Arcade::Inputs::IKEY_B},
                {SDLK_c, Arcade::Inputs::IKEY_C},
                {SDLK_d, Arcade::Inputs::IKEY_D},
                {SDLK_e, Arcade::Inputs::IKEY_E},
                {SDLK_f, Arcade::Inputs::IKEY_F},
                {SDLK_g, Arcade::Inputs::IKEY_G},
                {SDLK_h, Arcade::Inputs::IKEY_H},
                {SDLK_i, Arcade::Inputs::IKEY_I},
                {SDLK_j, Arcade::Inputs::IKEY_J},
                {SDLK_k, Arcade::Inputs::IKEY_K},
                {SDLK_l, Arcade::Inputs::IKEY_L},
                {SDLK_m, Arcade::Inputs::IKEY_M},
                {SDLK_n, Arcade::Inputs::IKEY_N},
                {SDLK_o, Arcade::Inputs::IKEY_O},
                {SDLK_p, Arcade::Inputs::IKEY_P},
                {SDLK_q, Arcade::Inputs::IKEY_Q},
                {SDLK_r, Arcade::Inputs::IKEY_R},
                {SDLK_s, Arcade::Inputs::IKEY_S},
                {SDLK_t, Arcade::Inputs::IKEY_T},
                {SDLK_u, Arcade::Inputs::IKEY_U},
                {SDLK_v, Arcade::Inputs::IKEY_V},
                {SDLK_w, Arcade::Inputs::IKEY_W},
                {SDLK_x, Arcade::Inputs::IKEY_X},
                {SDLK_y, Arcade::Inputs::IKEY_Y},
                {SDLK_z, Arcade::Inputs::IKEY_Z}
            };
    };
}
