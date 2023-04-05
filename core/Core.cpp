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
    _currentLib = 0;
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
    if (lib.isKeyPressed(Arcade::Inputs::IKEY_LEFT))
        _menuObjects[0]->setPosition({_menuObjects[0]->getPosition().first - 10, _menuObjects[0]->getPosition().second});
    if (lib.isKeyPressed(Arcade::Inputs::IKEY_RIGHT))
        _menuObjects[0]->setPosition({_menuObjects[0]->getPosition().first + 10, _menuObjects[0]->getPosition().second});
    if (lib.isKeyPressed(Arcade::Inputs::IKEY_UP))
        _menuObjects[0]->setPosition({_menuObjects[0]->getPosition().first, _menuObjects[0]->getPosition().second - 10});
    if (lib.isKeyPressed(Arcade::Inputs::IKEY_DOWN))
        _menuObjects[0]->setPosition({_menuObjects[0]->getPosition().first, _menuObjects[0]->getPosition().second + 10});
}

void Arcade::Core::renderMainMenu(Arcade::ILib &lib)
{
    lib.drawText("ARCADE", Arcade::Colors::BLUE, 100, {800,0});
    lib.drawText("Games", Arcade::Colors::BLUE, 100, {10,150});
    lib.drawText("Libraries", Arcade::Colors::BLUE, 100, {490,150});
    lib.drawText("HighScores", Arcade::Colors::BLUE, 75, {970,175});
    lib.drawText("UserName", Arcade::Colors::BLUE, 100, {1440,150});
    for (size_t i = 0; i < _menuObjects.size(); i++)
        lib.drawObjets(_menuObjects[i]);
    for (size_t i = 0; i < _gamesPath.size(); i++)
        lib.drawText(_gamesPath[i], Arcade::Colors::BLUE, 40, {10,300 + (i * 150)});
    for (size_t i = 0; i < _libsPath.size(); i++)
        lib.drawText(_libsPath[i], Arcade::Colors::BLUE, 40, {490,300 + (i * 150)});
    lib.drawShapes(Arcade::Shapes::SQUARE, Arcade::Colors::BLUE, {480, 150}, {2, 1080});
    lib.drawShapes(Arcade::Shapes::SQUARE, Arcade::Colors::BLUE, {960, 150}, {2, 1080});
    lib.drawShapes(Arcade::Shapes::SQUARE, Arcade::Colors::BLUE, {1440, 150}, {2, 1080});
    lib.drawShapes(Arcade::Shapes::SQUARE, Arcade::Colors::BLUE, {0, 150}, {2000, 2});
    lib.drawShapes(Arcade::Shapes::SQUARE, Arcade::Colors::BLUE, {0, 300}, {2000, 2});
}

void Arcade::Core::globalInputs(Arcade::ILib &lib)
{
    if (lib.isKeyPressed(Arcade::Inputs::IKEY_Q) && !lib.isWindowClosed()) {
        _currentScene = Arcade::Scenes::LEAVE;
        lib.closeWindow();
        return;
    }
    if (lib.isKeyPressed(Arcade::Inputs::IKEY_H) && !lib.isWindowClosed()) {
        if (_currentGame == _gamesPath.size() - 1) {
            _currentGame = 0;
        } else {
            _currentGame++;
        }
        loadGame(_gamesPath[_currentGame]);
        return;
    }
    if (lib.isKeyPressed(Arcade::Inputs::IKEY_G) && !lib.isWindowClosed()) {
        if (_currentLib == _libsPath.size() - 1) {
            _currentLib = 0;
        } else {
            _currentLib++;
        }
        loadLib(_libsPath[_currentLib]);
    }
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
        _lib.second->clearWindow();
        _lib.second.get()->updateEvent();
        globalInputs(*_lib.second.get());
        updateDeltaTime();
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
        std::shared_ptr<Arcade::IGame> var = _game.first.loadGameLib(GameName);
        _game.second = var;
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
