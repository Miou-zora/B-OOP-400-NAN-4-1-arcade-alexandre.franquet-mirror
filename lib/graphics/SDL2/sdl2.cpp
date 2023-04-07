/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-alexandre.franquet-mirror
** File description:
** sdl2
*/

#include "sdl2.hpp"
#include <iostream>

extern "C"
{
    Arcade::ILib *DisplayEntryPoint()
    {
        return new Arcade::SdlDisplayModule();
    }
}

Arcade::SdlDisplayModule::SdlDisplayModule(void): _window(nullptr), _renderer(nullptr)
{
}

Arcade::SdlDisplayModule::~SdlDisplayModule()
{
    if (_window != nullptr)
        closeWindow();
}

void Arcade::SdlDisplayModule::createWindow(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cerr << "Arcade::SdlDisplayModule::createWindow: " << SDL_GetError() << ".\n" << std::endl;
    if(SDL_VideoInit(NULL) < 0)
        std::cerr << "Arcade::SdlDisplayModule::createWindow: " << SDL_GetError() << ".\n" << std::endl;
    if (TTF_Init() < 0)
        std::cerr << "Arcade::SdlDisplayModule::createWindow: " << SDL_GetError() << ".\n" << std::endl;
    _window = SDL_CreateWindow("Arcade SDL",SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            1920,
                                            1080,
                                            SDL_WINDOW_SHOWN);
    if (_window == nullptr)
        std::cerr << "Arcade::SdlDisplayModule::createWindow: " << SDL_GetError() << ".\n" << std::endl;
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr)
        std::cerr << "Arcade::SdlDisplayModule::createWindow: " << SDL_GetError() << ".\n" << std::endl;
    SDL_RenderPresent(_renderer);
    _font = TTF_OpenFont("lib/graphics/arial.ttf", 24);
}

void Arcade::SdlDisplayModule::closeWindow(void)
{
    if (_font != nullptr)
        TTF_CloseFont(_font);
    _font = nullptr;
    if (_renderer != nullptr)
        SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;
    if (_window != nullptr)
        SDL_DestroyWindow(_window);
    _window = nullptr;
    TTF_Quit();
    SDL_Quit();
}

void Arcade::SdlDisplayModule::clearWindow(void)
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 1);
    SDL_RenderClear(_renderer);
}

void Arcade::SdlDisplayModule::renderWindow(void)
{
    SDL_RenderPresent(_renderer);
}

bool Arcade::SdlDisplayModule::isWindowClosed(void)
{
    if (_window == nullptr)
        return (true);
    return (false);
}

void Arcade::SdlDisplayModule::updateEvent(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            _keys[Arcade::Inputs::IKEY_S] = true;
        if (_keyMap.count(event.key.keysym.sym)) {
            if (event.type == SDL_KEYDOWN) {
                _keys[_keyMap[event.key.keysym.sym]] = true;
            }
            if (event.type == SDL_KEYUP) {
                _keys[_keyMap[event.key.keysym.sym]] = false;
            }
        }
    }
}

void Arcade::SdlDisplayModule::drawObjets(std::shared_ptr<Arcade::IObject> object)
{
    (void)(object);
    SDL_Rect rect;
    rect.x = object->getPosition().first * 30;
    rect.y = object->getPosition().second * 30;
    rect.w = object->getSize().first * 30;
    rect.h = object->getSize().second * 30;
    SDL_Color color = arcadeColorToSfColor(object->getColor());
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_renderer, &rect);
}

SDL_Color Arcade::SdlDisplayModule::arcadeColorToSfColor(Arcade::Colors colors)
{
    switch (colors) {
        case Arcade::Colors::BLACK:
            return SDL_Color{0, 0, 0, 255};
        case Arcade::Colors::WHITE:
            return SDL_Color{255, 255, 255, 255};
        case Arcade::Colors::RED:
            return SDL_Color{255, 0, 0, 255};
        case Arcade::Colors::GREEN:
            return SDL_Color{0, 255, 0, 255};
        case Arcade::Colors::BLUE:
            return SDL_Color{0, 0, 255, 255};
        case Arcade::Colors::YELLOW:
            return SDL_Color{255, 255, 0, 255};
        case Arcade::Colors::MAGENTA:
            return SDL_Color{255, 0, 255, 255};
        case Arcade::Colors::CYAN:
            return SDL_Color{0, 255, 255, 255};
        case Arcade::Colors::TRANSPARENT:
            return SDL_Color{0, 0, 0, 0};
        default:
            return SDL_Color{0, 0, 0, 255};
    }
}

void Arcade::SdlDisplayModule::drawShapes(Arcade::Shapes shape, Arcade::Colors colors, std::pair<ssize_t, ssize_t> pos, std::pair<ssize_t, ssize_t> size)
{
    (void)(shape);
    SDL_Rect rect;
    rect.x = pos.first * 30;
    rect.y = pos.second * 30;
    rect.w = size.first * 30;
    rect.h = size.second * 30;
    SDL_Color color = arcadeColorToSfColor(colors);
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_renderer, &rect);
}

void Arcade::SdlDisplayModule::drawText(std::shared_ptr<Arcade::Text> text)
{
    if (_font == nullptr) {
        std::cerr << "Arcade::SdlDisplayModule::drawText:" << std::endl;
        return;
    }
    SDL_Color sdlColor = arcadeColorToSfColor(text->getColor());
    SDL_Surface *surface = TTF_RenderText_Solid(_font, text->getText().c_str(), sdlColor);
    if (surface == nullptr) {
        std::cerr << "Arcade::SdlDisplayModule::drawText: " << SDL_GetError() << ".\n" << std::endl;
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Arcade::SdlDisplayModule::drawText: " << SDL_GetError() << ".\n" << std::endl;
        return;
    }
    SDL_Rect rect;
    rect.x = text->getPosition().first * 30;
    rect.y = text->getPosition().second * 30;
    rect.w = 60;
    rect.h = 20;
    SDL_RenderCopy(_renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Arcade::SdlDisplayModule::drawText(std::string str, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> pos)
{
    if (_font == nullptr) {
        std::cerr << "Arcade::SdlDisplayModule::drawText:" << std::endl;
        return;
    }
    SDL_Color sdlColor = arcadeColorToSfColor(color);
    SDL_Surface *surface = TTF_RenderText_Solid(_font, str.c_str(), sdlColor);
    if (surface == nullptr) {
        std::cerr << "Arcade::SdlDisplayModule::drawText: " << SDL_GetError() << ".\n" << std::endl;
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Arcade::SdlDisplayModule::drawText: " << SDL_GetError() << ".\n" << std::endl;
        return;
    }
    SDL_Rect rect;
    rect.x = pos.first * 30;
    rect.y = pos.second * 30;
    rect.w = size * 60;
    rect.h = size * 20;
    SDL_RenderCopy(_renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

bool Arcade::SdlDisplayModule::isKeyPressed(Arcade::Inputs input)
{
    return _keys[input];
}

bool Arcade::SdlDisplayModule::isKeyReleased(Arcade::Inputs input)
{
    return !_keys[input];

}
