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
}

void Arcade::SdlDisplayModule::closeWindow(void)
{
    TTF_CloseFont(_fonts["arial.ttf"]);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
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
            _keys[Arcade::Inputs::IKEY_Q] = true;
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
    if (object->getShape() == Arcade::Shapes::SQUARE) {
        SDL_Rect rect;
        rect.x = object->getPosition().first;
        rect.y = object->getPosition().second;
        rect.w = object->getSize().first;
        rect.h = object->getSize().second;
        SDL_Color color = arcadeColorToSfColor(object->getColor());
        SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(_renderer, &rect);
    }
}

SDL_Color Arcade::SdlDisplayModule::arcadeColorToSfColor(Arcade::Colors colors)
{
    switch (colors) {
        case Arcade::Colors::BLACK:
            return SDL_Color{0, 0, 0, 1};
        case Arcade::Colors::WHITE:
            return SDL_Color{255, 255, 255, 1};
        case Arcade::Colors::RED:
            return SDL_Color{255, 0, 0, 1};
        case Arcade::Colors::GREEN:
            return SDL_Color{0, 255, 0, 1};
        case Arcade::Colors::BLUE:
            return SDL_Color{0, 0, 255, 1};
        case Arcade::Colors::YELLOW:
            return SDL_Color{255, 255, 0, 1};
        case Arcade::Colors::MAGENTA:
            return SDL_Color{255, 0, 255, 1};
        case Arcade::Colors::CYAN:
            return SDL_Color{0, 255, 255, 1};
        case Arcade::Colors::TRANSPARENT:
            return SDL_Color{0, 0, 0, 0};
        default:
            return SDL_Color{0, 0, 0, 1};
    }
}

void Arcade::SdlDisplayModule::drawShapes(Arcade::Shapes shape, Arcade::Colors colors, std::pair<ssize_t, ssize_t> pos, std::pair<ssize_t, ssize_t> size)
{
    if (shape == Arcade::Shapes::SQUARE) {
        SDL_Rect rect;
        rect.x = pos.first;
        rect.y = pos.second;
        rect.w = size.first;
        rect.h = size.second;
        SDL_Color color = arcadeColorToSfColor(colors);
        SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(_renderer, &rect);
    }
}


void Arcade::SdlDisplayModule::drawText(std::shared_ptr<Arcade::Text> text)
{
    std::cout << "drawTextt" << std::endl;
    if (_fonts.count("arial.ttf") == 0) {
        _fonts["arial.ttf"] = TTF_OpenFont("../arial.ttf", 100);
        if (_fonts["arial.ttf"] == nullptr)
            std::cerr << "Arcade::SdlDisplayModule::drawText: " << SDL_GetError() << ".\n" << std::endl;
    }
    SDL_Color sdlColor = arcadeColorToSfColor(text->getColor());
    SDL_Surface *surface = TTF_RenderText_Solid(_fonts["arial.ttf"], text->getText().c_str(), sdlColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect rectt;
    rectt.x = text->getPosition().first;
    rectt.y = text->getPosition().second;
    rectt.w = 100;
    rectt.h = 100;
    SDL_RenderCopy(_renderer, texture, NULL, &rectt);
}


void Arcade::SdlDisplayModule::drawText(std::string str, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> pos)
{
    if (_fonts.count("arial.ttf") == 0) {
        _fonts["arial.ttf"] = TTF_OpenFont("./lib/graphics/arial.ttf", 25);
        if (_fonts["arial.ttf"] == nullptr)
            std::cerr << "Arcade::SdlDisplayModule::drawText: " << SDL_GetError() << ".\n" << std::endl;
    }
    SDL_Color sdlColor = arcadeColorToSfColor(color);
    SDL_Surface *surface = TTF_RenderText_Solid(_fonts["arial.ttf"], str.c_str(), sdlColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect rect;
    rect.x = pos.first;
    rect.y = pos.second;
    rect.w = size;
    rect.h = size;
    SDL_RenderCopy(_renderer, texture, NULL, &rect);
}


bool Arcade::SdlDisplayModule::isKeyPressed(Arcade::Inputs input)
{
    return _keys[input];
}


bool Arcade::SdlDisplayModule::isKeyReleased(Arcade::Inputs input)
{
    return !_keys[input];

}

