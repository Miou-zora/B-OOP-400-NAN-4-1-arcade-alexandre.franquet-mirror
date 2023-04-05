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

Arcade::SdlDisplayModule::SdlDisplayModule(void)
{
}

Arcade::SdlDisplayModule::~SdlDisplayModule()
{
}

void Arcade::SdlDisplayModule::createWindow(void)
{
    _window = SDL_CreateWindow("Arcade SDL",SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            1920,
                                            1080,
                                            SDL_WINDOW_SHOWN);
    if (_window == nullptr) {
        std::cerr << "Arcade::SdlDisplayModule::createWindow: " << SDL_GetError() << ".\n" << std::endl;
    }
}

void Arcade::SdlDisplayModule::closeWindow(void)
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Arcade::SdlDisplayModule::clearWindow(void)
{
}

void Arcade::SdlDisplayModule::renderWindow(void)
{

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
            if (event.type == SDL_KEYUP) {
                _keys[_keyMap[event.key.keysym.sym]] = true;
            }
            if (event.type == SDL_KEYDOWN) {
                _keys[_keyMap[event.key.keysym.sym]] = false;
            }
        }
    }
}


void Arcade::SdlDisplayModule::drawObjets(std::shared_ptr<Arcade::IObject> object)
{
    (void)object;
}


void Arcade::SdlDisplayModule::drawShapes(Arcade::Shapes shape, Arcade::Colors color, std::pair<ssize_t, ssize_t> pos, std::pair<ssize_t, ssize_t> size)
{
    (void)shape;
    (void)color;
    (void)pos;
    (void)size;
}


void Arcade::SdlDisplayModule::drawText(std::shared_ptr<Arcade::Text> text)
{
    (void)text;
}


void Arcade::SdlDisplayModule::drawText(std::string str, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> pos)
{
    (void)str;
    (void)size;
    (void)color;
    (void)pos;
}


bool Arcade::SdlDisplayModule::isKeyPressed(Arcade::Inputs input)
{
    return _keys[input];
}


bool Arcade::SdlDisplayModule::isKeyReleased(Arcade::Inputs input)
{
    return !_keys[input];

}

