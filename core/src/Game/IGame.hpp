/*
** EPITECH PROJECT, 2023
** arcade-archi
** File description:
** IGame
*/

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "Lib/ILib.hpp"

namespace Arcade {
    enum gameState {
        MENU,
        GAME,
        PAUSE,
        END
    };

    class IGame {
        public:
            IGame(void) = default;
            virtual ~IGame() = default;

            virtual void load(void) = 0;
            virtual void update(Arcade::ILib &lib, float seconds) = 0;
            virtual void render(Arcade::ILib &lib) = 0;
            virtual void reset(void) = 0;
            virtual void unload(void) = 0;

            virtual Arcade::gameState getState(void) const = 0;
            virtual ssize_t getScore(void) const = 0;
            virtual ssize_t getHighScore(void) const = 0;
            virtual std::string getGameName(void) const = 0;
    };
};
