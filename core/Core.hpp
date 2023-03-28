/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** Arcade
*/

#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>

#include "IGame.hpp"
#include "IEvent.hpp"
#include "IDisplay.hpp"
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

            void runScene(Arcade::Scenes scene = Arcade::MAIN_MENU);
            bool loadGame(const std::string &GameName) { (void)GameName; return true; };
            bool loadLib(const std::string &LibName) { (void)LibName; return true; };
            void loop();

        protected:
        private:
            void displayMainMenu();
            void updateMainMenu();
            void handleEvents() {};

            Arcade::LibLoader<Arcade::IDisplay> _displayLoader;
            Arcade::LibLoader<Arcade::IEvent> _eventLoader;
            Arcade::LibLoader<Arcade::IGame> _gameLoader;

            std::vector<std::string> _games;
            std::vector<std::string> _libs;
            std::size_t _currentGame;
            std::size_t _currentLib;
            std::shared_ptr<Arcade::IDisplay> _display;
            std::shared_ptr<Arcade::IGame> _game;
            std::shared_ptr<Arcade::IEvent> _events;
            Arcade::Scenes _currentScene;
    };
};