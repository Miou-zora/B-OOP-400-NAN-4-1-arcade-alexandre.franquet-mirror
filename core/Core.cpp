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
    } catch (const LoaderException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    _startTime = std::chrono::high_resolution_clock::now();
    _currentScene = Arcade::Scenes::MAIN_MENU;
    for (size_t i = 0; i < _libsPath.size(); i++) {
        if (_libsPath[i] == libFilePath)
            _currentLib = i;
    }
    _currentGame = 0;
    if (_libsPath.size() == 0 || _gamesPath.size() == 0) {
        std::cerr << "No library found" << std::endl;
        exit(84);
    }
    _lib.second.get()->createWindow();
    initMenu();
}

Arcade::Core::~Core()
{
    _lib.first.closeLib();
}

void Arcade::Core::initMenu()
{
    std::shared_ptr<Arcade::AObject> game = std::make_shared<Arcade::AObject>();
    game->setPosition({100, 100});
    game->setShape(Arcade::Shapes::SQUARE);
    game->setSize({100, 100});
    game->setColor(Arcade::Colors::WHITE);
    _menuObjects.push_back(game);
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
    (void)lib;
}

void Arcade::Core::globalInputs(Arcade::ILib &lib)
{
    if (lib.isKeyPressed(Arcade::Inputs::IKEY_S) && !lib.isWindowClosed()) {
        _currentScene = Arcade::Scenes::LEAVE;
        lib.closeWindow();
        return;
    }
    if (lib.isKeyPressed(Arcade::Inputs::IKEY_D) && !lib.isWindowClosed()) {
        if (_currentGame == _gamesPath.size() - 1) {
            _currentGame = 0;
        } else {
            _currentGame++;
        }
        loadGame(_gamesPath[_currentGame]);
        return;
    }
    if (lib.isKeyPressed(Arcade::Inputs::IKEY_B) && !lib.isWindowClosed()) {
        if (_currentLib == _libsPath.size() - 1) {
            _currentLib = 0;
        } else {
            _currentLib++;
        }
        loadLib(_libsPath[_currentLib]);
        return;
    }
    if (lib.isKeyPressed(Arcade::Inputs::IKEY_M) && !lib.isWindowClosed()) {
        _currentScene = Arcade::Scenes::MAIN_MENU;
        return;
    }
}

void Arcade::Core::updateDeltaTime(void)
{
    std::chrono::_V2::system_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    _deltaTime = std::chrono::duration<double, std::milli>(endTime-_startTime).count();
    _startTime = endTime;
}

void Arcade::Core::wait(double time)
{
    clock_t time_to_wait = clock() + time * CLOCKS_PER_SEC;

    while (clock() < time_to_wait) {
        globalInputs(*_lib.second.get());
    }
}

void Arcade::Core::loop()
{
    while (_currentScene != Arcade::Scenes::LEAVE) {
        _lib.second.get()->updateEvent();
        updateDeltaTime();
        wait(0.01);
        _lib.second->clearWindow();
        runScene(_currentScene);
        _lib.second->renderWindow();
    }
}

bool Arcade::Core::loadGame(const std::string &GameName)
{
    try {
        if (_game.second) {
            _game.second.get()->unload();
            _game.second.reset();
        }
        if (_game.first.isLibOpen())
            _game.first.closeLib();
        _game.second = _game.first.loadGameLib(GameName);
        _game.second.get()->load();
        _currentScene = Arcade::Scenes::IN_GAME;
    } catch (const LoaderException &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool Arcade::Core::loadLib(const std::string &LibName)
{
    try {
        if (_lib.second) {
            _lib.second.get()->closeWindow();
            _lib.second.reset();
        }
        if (_lib.first.isLibOpen())
            _lib.first.closeLib();
        _lib.second = _lib.first.loadGraphicalLib(LibName);
        _lib.second.get()->createWindow();
    } catch (const LoaderException &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}
