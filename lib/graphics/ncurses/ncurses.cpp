/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-alexandre.franquet-mirror
** File description:
** sdl2
*/

#include "ncurses.hpp"
#include <iostream>
#include "AObjects.hpp"

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
    curs_set(false);
    resizeterm(80,24);
    refresh();
    start_color();
    init_pair(Arcade::Colors::RED, COLOR_BLACK, COLOR_RED);
    init_pair(Arcade::Colors::GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(Arcade::Colors::YELLOW, COLOR_BLACK, COLOR_YELLOW);
    init_pair(Arcade::Colors::BLUE, COLOR_BLACK, COLOR_BLUE);
    init_pair(Arcade::Colors::MAGENTA, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(Arcade::Colors::CYAN, COLOR_BLACK, COLOR_CYAN);
    init_pair(Arcade::Colors::WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(Arcade::Colors::BLACK, COLOR_WHITE, COLOR_BLACK);
}

void Arcade::NcursesDisplayModule::closeWindow(void)
{
    keypad(stdscr, false);
    nodelay(stdscr, false);
    curs_set(true);
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

    if (ch != ERR) {
        _keys[_keyMap[ch]] = true;
    }
}


void Arcade::NcursesDisplayModule::drawObjets(std::shared_ptr<Arcade::IObject> object)
{
    if (object->getShape() == Arcade::Shapes::SQUARE) {
        attron(COLOR_PAIR(object->getColor()));
        mvprintw(object->getPosition().second / 30, object->getPosition().first / 30, "#");
        attroff(COLOR_PAIR(object->getColor()));
    } else if (object->getShape() == Arcade::Shapes::CIRCLE) {
        attron(COLOR_PAIR(object->getColor()));
        mvprintw(object->getPosition().second / 30, object->getPosition().first / 30, "()");
        attroff(COLOR_PAIR(object->getColor()));
    } else if (object->getShape() == Arcade::Shapes::TRIANGLE) {
        attron(COLOR_PAIR(object->getColor()));
        mvprintw(object->getPosition().second / 30, object->getPosition().first / 30, "<>");
        attroff(COLOR_PAIR(object->getColor()));
    }
}


void Arcade::NcursesDisplayModule::drawShapes(Arcade::Shapes shape, Arcade::Colors color, std::pair<ssize_t, ssize_t> pos, std::pair<ssize_t, ssize_t> size)
{
    std::shared_ptr<Arcade::IObject> object = std::make_shared<Arcade::AObject>();
    object->setShape(shape);
    object->setColor(color);
    object->setPosition(pos);
    object->setSize(size);
    drawObjets(object);
}


void Arcade::NcursesDisplayModule::drawText(std::shared_ptr<Arcade::Text> text)
{
    attron(COLOR_PAIR(text->getColor()));
    mvprintw(text->getPosition().second, text->getPosition().first * 2, text->getText().c_str());
    attroff(COLOR_PAIR(text->getColor()));
}


void Arcade::NcursesDisplayModule::drawText(std::string str, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> pos)
{
    attron(COLOR_PAIR(color));
    mvprintw(pos.second / 30, pos.first / 30, str.c_str());
    attroff(COLOR_PAIR(color));
    (void)size;
}


bool Arcade::NcursesDisplayModule::isKeyPressed(Arcade::Inputs key)
{
    bool return_value = _keys[key];
    _keys[key] = false;
    return (return_value);
}


bool Arcade::NcursesDisplayModule::isKeyReleased(Arcade::Inputs key)
{
    return (!isKeyPressed(key));
}

