/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** Arcade
*/

#pragma once
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <dirent.h>
#include <algorithm>

#include "IGame.hpp"
#include "Lib/ILib.hpp"
#include "LibLoader.hpp"

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

        private:
            void runScene(Arcade::Scenes scene = Arcade::MAIN_MENU);
            bool loadGame(const std::string &GameName);
            bool loadLib(const std::string &LibName);

            std::vector<std::string> getLibsFromDirectory();
            void storeLibsPath();

            std::pair<Arcade::LibLoader<Arcade::ILib>, std::shared_ptr<Arcade::ILib>> _lib;
            std::pair<Arcade::LibLoader<Arcade::IGame>, std::shared_ptr<Arcade::IGame>> _game;

            std::vector<std::string> _gamesPath;
            std::vector<std::string> _libsPath;

            std::size_t _currentGame;
            std::size_t _currentLib;
            Arcade::Scenes _currentScene;
    };
};