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

}

void Arcade::SdlDisplayModule::closeWindow(void)
{

}

void Arcade::SdlDisplayModule::clearWindow(void)
{

}

void Arcade::SdlDisplayModule::renderWindow(void)
{

}

bool Arcade::SdlDisplayModule::isWindowClosed(void)
{
    return (true);
}

void Arcade::SdlDisplayModule::updateEvent(void)
{

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


bool Arcade::SdlDisplayModule::isKeyPressed(Arcade::Inputs key)
{
    (void)key;
    return (false);
}


bool Arcade::SdlDisplayModule::isKeyReleased(Arcade::Inputs key)
{
    (void)key;
    return (false);
}

