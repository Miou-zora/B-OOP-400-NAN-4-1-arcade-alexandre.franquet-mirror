/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** Arcade
*/

#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <time.h>
#include <chrono>

#include "IGame.hpp"
#include "Lib/ILib.hpp"
#include "LibLoader.hpp"
#include "AObjects.hpp"

namespace Arcade {
    /*Those are just example */

    enum Scenes {
        MAIN_MENU,
        IN_GAME,
        LEAVE
    };

    class Core {
        public:
            Core(std::string libFilePath);
            ~Core();

            void loop();

            float getDeltaTime() const { return _deltaTime; };

        private:
            void runScene(Arcade::Scenes scene = Arcade::MAIN_MENU);
            bool loadGame(const std::string &GameName);
            bool loadLib(const std::string &LibName);
            void updateDeltaTime(void);

            void updateMainMenu(Arcade::ILib &lib);
            void renderMainMenu(Arcade::ILib &lib);
            void initMenu();
            void wait(double time);

            void globalInputs(Arcade::ILib &lib);

            std::vector<std::string> getLibsFromDirectory();
            void storeLibsPath();

            std::pair<Arcade::LibLoader<Arcade::ILib>, std::shared_ptr<Arcade::ILib>> _lib;
            std::pair<Arcade::LibLoader<Arcade::IGame>, std::shared_ptr<Arcade::IGame>> _game;

            std::vector<std::string> _gamesPath;
            std::vector<std::string> _libsPath;

            std::size_t _currentGame;
            std::size_t _currentLib;
            Arcade::Scenes _currentScene;

            double _deltaTime;
            std::chrono::_V2::system_clock::time_point _startTime;

            std::vector<std::shared_ptr<Arcade::IObject>> _menuObjects;
    };
};
