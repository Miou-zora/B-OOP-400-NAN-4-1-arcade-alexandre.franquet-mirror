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
#include "IEvent.hpp"
#include "IDisplay.hpp"

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
            virtual void update(std::shared_ptr<IEvent> events, float seconds) = 0;
            virtual void render(Arcade::IDisplay module) = 0;
            virtual void reset(void) = 0;
            virtual void unload(void) = 0;

            virtual Arcade::gameState getState(void) const = 0;
            virtual ssize_t getScore(void) const = 0;
            virtual ssize_t getHighScore(void) const = 0;
            virtual std::string getGameName(void) const = 0;

            virtual void setIEvents(std::shared_ptr<Arcade::IEvent> event) = 0;
            virtual void setIDisplay(std::shared_ptr<Arcade::IDisplay> display) = 0;
    };
};
