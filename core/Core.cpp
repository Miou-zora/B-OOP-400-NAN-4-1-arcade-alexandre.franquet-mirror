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
        storeLibsPath();
        _lib.second = _lib.first.loadGraphicalLib(libFilePath);
        _game.second = _game.first.loadGameLib("./lib/lib_snake.so");
    } catch (const LoaderException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    _startTime = std::chrono::high_resolution_clock::now();
    _currentScene = Arcade::Scenes::IN_GAME;
    _currentLib = std::find(_libsPath.begin(), _libsPath.end(), libFilePath) - _libsPath.begin();
    _currentGame = 0;
    _lib.second.get()->createWindow();
    _game.second.get()->load();
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
        }
        catch (const LoaderException &e) {
            try {
                if (_lib.first.loadGraphicalLib(lib)) {
                    _libsPath.push_back(lib);
                    _lib.first.closeLib();
                }
            }
            catch (const LoaderException &err) {
                std::cout << lib << " bad library" << std::endl;
            }
        }
    }
}

std::vector<std::string> Arcade::Core::getLibsFromDirectory()
{
    std::string path = "./lib/";
    std::vector<std::string> libs;

    if (!std::filesystem::exists(path))
        throw LoaderException("Error while loading libs");
    try {
        for (const auto &entry : std::filesystem::directory_iterator(path))
            if (entry.path().extension() == ".so")
                libs.push_back(path + entry.path().filename().string());
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << e.what() << std::endl;
        throw LoaderException("Error while loading libs");
    }
    return libs;
}

void Arcade::Core::runScene(Arcade::Scenes scene)
{
    switch (scene) {
        case Arcade::Scenes::MAIN_MENU:
            updateMainMenu(*_lib.second.get());
            renderMainMenu(*_lib.second.get());
            break;
        case Arcade::Scenes::IN_GAME:
            _game.second.get()->update(*_lib.second.get(), _deltaTime);
            _game.second.get()->render(*_lib.second.get());
            break;
        case Arcade::Scenes::LEAVE:
            break;
    }
}

void Arcade::Core::updateMainMenu(Arcade::ILib &lib)
{
    (void)lib;
}

void Arcade::Core::renderMainMenu(Arcade::ILib &lib)
{
    lib.clearWindow();

    lib.renderWindow();
}

void Arcade::Core::updateDeltaTime(void)
{
    std::chrono::_V2::system_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    _deltaTime = std::chrono::duration<double, std::milli>(endTime-_startTime).count();
    _startTime = endTime;
}

void Arcade::Core::loop()
{
    while (_currentScene != Arcade::Scenes::LEAVE) {
        updateDeltaTime();
        _lib.second.get()->updateEvent();
        // runScene(_currentScene);
        _lib.second.get()->clearWindow();
        _game.second.get()->render(*_lib.second.get());
        _lib.second.get()->renderWindow();
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
