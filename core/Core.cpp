/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-alexandre.franquet-mirror
** File description:
** Arcade
*/

#include "Core.hpp"

Arcade::Core::Core(std::string libFilePath)
{
    _currentScene = Arcade::Scenes::MAIN_MENU;
    try {
        _display = _displayLoader.loadLib(libFilePath);
    } catch (const LoaderException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    _libs.push_back(libFilePath);
    _currentLib = 0;
    _currentGame = 0;
    _display.get()->createWindow();
}

Arcade::Core::~Core()
{
}

void Arcade::Core::displayMainMenu()
{
    _display.get()->renderWindow();
}

void Arcade::Core::runScene(Arcade::Scenes scene)
{
    switch (scene) {
        case Arcade::Scenes::MAIN_MENU:
            displayMainMenu();
            break;
        case Arcade::Scenes::IN_GAME:
            break;
        case Arcade::Scenes::LEAVE:
            break;
    }
}

void Arcade::Core::loop()
{
    while (_currentScene != Arcade::Scenes::LEAVE) {
        runScene(_currentScene);
        handleEvents();
    }
}
