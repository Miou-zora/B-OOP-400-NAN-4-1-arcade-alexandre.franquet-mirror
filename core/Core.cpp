/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-alexandre.franquet-mirror
** File description:
** Arcade
*/

#include "Core.hpp"

Arcade::Core::Core(std::string libFilePath)
{
    storeLibsPath();
    try {
        _lib.second = _lib.first.loadGraphicalLib(libFilePath);
    } catch (const LoaderException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    _currentScene = Arcade::Scenes::MAIN_MENU;
    _currentLib = std::find(_libsPath.begin(), _libsPath.end(), libFilePath) - _libsPath.begin();
    _currentGame = 0;
    _lib.second.get()->createWindow();
}

Arcade::Core::~Core()
{
    _lib.first.closeLib();
}

void Arcade::Core::storeLibsPath()
{
    for (auto &lib : getLibsFromDirectory()) {
        try {
            if (_lib.first.loadGameLib(lib)) {
                _gamesPath.push_back(lib);
                _lib.first.closeLib();
            }
        } catch (const LoaderException &e) {
            try {
                if (_lib.first.loadGraphicalLib(lib)) {
                    _libsPath.push_back(lib);
                    _lib.first.closeLib();
                }
            } catch (const LoaderException &err) {
                std::cout << lib << " bad library" << std::endl;
            }
        }
    }
}

std::vector<std::string> Arcade::Core::getLibsFromDirectory()
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

void Arcade::Core::runScene(Arcade::Scenes scene)
{
    switch (scene) {
        case Arcade::Scenes::MAIN_MENU:
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
    }
}

bool Arcade::Core::loadGame(const std::string &GameName)
{
    try {
        _game.second = _game.first.loadGameLib(GameName);
    } catch (const LoaderException &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool Arcade::Core::loadLib(const std::string &LibName)
{
    try {
        _lib.second = _lib.first.loadGraphicalLib(LibName);
    } catch (const LoaderException &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}