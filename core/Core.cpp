/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-alexandre.franquet-mirror
** File description:
** Arcade
*/

#include "Core.hpp"

Arcade::Core::Core(std::string libFilePath)
{
    try {
        _lib.second = _lib.first.loadLib(libFilePath);
        loadLibsFromDirectory();
    } catch (const LoaderException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    _currentScene = Arcade::Scenes::MAIN_MENU;
    _currentLib = 0;
    _currentGame = 0;
    _lib.second.get()->createWindow();
}

Arcade::Core::~Core()
{
    _lib.first.closeLib();
}

std::vector<std::string> Arcade::Core::loadLibsFromDirectory()
{
    DIR *dir;
    struct dirent *ent;
    std::string path = "./lib/";
    std::vector<std::string> libs;

    if ((dir = opendir("./lib")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.' && strlen(ent->d_name) > 3 && !strcmp(ent->d_name + strlen(ent->d_name) - 3, ".so")) {
                libs.push_back(path + ent->d_name);
            }
        }
        closedir(dir);
    } else {
        throw LoaderException("Couldn't open directory");
    }
    return libs;
}

void Arcade::Core::displayMainMenu()
{
    _lib.second.get()->renderWindow();
    _lib.second.get()->drawText("Arcade Menu", Arcade::Colors::BLUE, 32, {0, 0});
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
    // while (_currentScene != Arcade::Scenes::LEAVE) {
        runScene(_currentScene);
        handleEvents();
    // }
}
