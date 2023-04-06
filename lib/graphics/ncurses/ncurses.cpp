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
    nodelay(stdscr, true);
    curs_set(FALSE);
    refresh();
    start_color();
    init_pair(Arcade::Colors::RED, COLOR_RED, COLOR_BLACK);
    init_pair(Arcade::Colors::GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(Arcade::Colors::BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(Arcade::Colors::YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(Arcade::Colors::MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(Arcade::Colors::CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(Arcade::Colors::WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(Arcade::Colors::BLACK, COLOR_BLACK, COLOR_BLACK);
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
    erase();
}

void Arcade::NcursesDisplayModule::renderWindow(void)
{
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
    if (object->getShape() == Arcade::Shapes::SQUARE) {
        mvprintw(object->getPosition().first, object->getPosition().second, "[]");
    }
}


void Arcade::NcursesDisplayModule::drawShapes(Arcade::Shapes shape, Arcade::Colors color, std::pair<ssize_t, ssize_t> pos, std::pair<ssize_t, ssize_t> size)
{
    if (shape == Arcade::Shapes::SQUARE) {
        attron(COLOR_PAIR(color));
        mvprintw((pos.first - 450) / 50, (pos.second - 450) / 50, "[]");
        attroff(COLOR_PAIR(color));
    }
    (void)size;
}


void Arcade::NcursesDisplayModule::drawText(std::shared_ptr<Arcade::Text> text)
{
    attron(COLOR_PAIR(text->getColor()));
    mvprintw(text->getPosition().first / 50, text->getPosition().second / 50, text->getText().c_str());
    attroff(COLOR_PAIR(text->getColor()));
}


void Arcade::NcursesDisplayModule::drawText(std::string str, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> pos)
{
    attron(COLOR_PAIR(color));
    mvprintw(pos.first / 50, pos.second / 50, str.c_str());
    attroff(COLOR_PAIR(color));
    (void)size;
}


bool Arcade::NcursesDisplayModule::isKeyPressed(Arcade::Inputs key)
{
    return (_keys[key]);
}


bool Arcade::NcursesDisplayModule::isKeyReleased(Arcade::Inputs key)
{
    return (!_keys[key]);
}

