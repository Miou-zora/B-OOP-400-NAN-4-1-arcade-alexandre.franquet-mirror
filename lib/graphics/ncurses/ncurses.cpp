/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-alexandre.franquet-mirror
** File description:
** sdl2
*/

#include "ncurses.hpp"
#include <iostream>

extern "C"
{
    Arcade::ILib *DisplayEntryPoint()
    {
        return new Arcade::NcursesDisplayModule();
    }
}

Arcade::NcursesDisplayModule::NcursesDisplayModule(void)
{
    for (auto &it : _keyMap) {
        _keys[it.second] = false;
    }
}

Arcade::NcursesDisplayModule::~NcursesDisplayModule()
{

}

void Arcade::NcursesDisplayModule::createWindow(void)
{
    _window = true;
    initscr();
    noecho();
    keypad(stdscr, true);
}

void Arcade::NcursesDisplayModule::closeWindow(void)
{
    keypad(stdscr, false);
    echo();
    endwin();
    _window = false;
}

void Arcade::NcursesDisplayModule::clearWindow(void)
{
    clear();
}

void Arcade::NcursesDisplayModule::renderWindow(void)
{
    curs_set(0);
    refresh();
}

bool Arcade::NcursesDisplayModule::isWindowClosed(void)
{
    if (_window == false)
        return (true);
    return (false);
}

void Arcade::NcursesDisplayModule::updateEvent(void)
{
    int ch = getch();

    for (auto &it : _keyMap) {
        _keys[it.second] = false;
    }
    if (ch != ERR) {
        _keys[_keyMap[ch]] = true;
    }
}


void Arcade::NcursesDisplayModule::drawObjets(std::shared_ptr<Arcade::IObject> object)
{
    move(0, 0);
    printw("%ld", object->getPosition().first);
    (void)object;
    // if (object->getShape() == Arcade::Shapes::SQUARE) {
    //     mvprintw(object->getPosition().first, object->getPosition().second, "[]");
    // }
}


void Arcade::NcursesDisplayModule::drawShapes(Arcade::Shapes shape, Arcade::Colors color, std::pair<ssize_t, ssize_t> pos, std::pair<ssize_t, ssize_t> size)
{
    (void)shape;
    (void)color;
    (void)pos;
    (void)size;
}


void Arcade::NcursesDisplayModule::drawText(std::shared_ptr<Arcade::Text> text)
{
    (void)text;
}


void Arcade::NcursesDisplayModule::drawText(std::string str, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> pos)
{
    (void)str;
    (void)size;
    (void)color;
    (void)pos;
}


bool Arcade::NcursesDisplayModule::isKeyPressed(Arcade::Inputs key)
{
    return (_keys[key]);
}


bool Arcade::NcursesDisplayModule::isKeyReleased(Arcade::Inputs key)
{
    return (!_keys[key]);
}

