/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-alexandre.franquet-mirror
** File description:
** snake
*/

#include "snake.hpp"
#include <iostream>

extern "C"
{
    Arcade::IGame *GameEntryPoint()
    {
        return new Arcade::SnakeGame();
    }
}

Arcade::SnakeGame::SnakeGame(void)
{
    _map = {
        "####################",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "####################"
    };
    _snake = {"sssS"};
    _food = "f";
}

Arcade::SnakeGame::~SnakeGame()
{
}

void Arcade::SnakeGame::update(Arcade::ILib &lib, float seconds)
{
    (void) seconds;
    (void) lib;
}

void Arcade::SnakeGame::reset()
{
}

void Arcade::SnakeGame::unload()
{
}

void Arcade::SnakeGame::generateMap(void)
{
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == '#') {
                std::shared_ptr<Arcade::AObject> wall = std::make_shared<Arcade::AObject>();
                wall->setShape(Arcade::Shapes::SQUARE);
                wall->setPosition({x, y});
                wall->setSize({1, 1});
                wall->setColor(Arcade::Colors::RED);
                wall->setFilePath("");
                _allObjects.push_back(wall);
            }
            if (_map[y][x] == ' ') {
                std::shared_ptr<Arcade::AObject> empty = std::make_shared<Arcade::AObject>();
                empty->setShape(Arcade::Shapes::SQUARE);
                empty->setPosition({x, y});
                empty->setSize({1, 1});
                empty->setColor(Arcade::Colors::BLACK);
                empty->setFilePath("");
                _allObjects.push_back(empty);
            }
        }
    }
}

void Arcade::SnakeGame::load(void)
{
    generateMap();
}

void Arcade::SnakeGame::render(Arcade::ILib &lib)
{
    for (auto &object : _allObjects) {
        lib.drawObjets(object);
    }
}
