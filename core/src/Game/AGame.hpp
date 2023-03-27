/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** AGame
*/

#pragma once
#include "IGame.hpp"
#include "Types.hpp"

namespace Arcade
{
    class AGame : virtual public Arcade::IGame {
        /**
         *  @brief The class AGame is the abstract class of the Game
         *  @details The methods are overriden but useless in this class
         *  @details But the attributes are used in the inherited classes
         **/

        public:
            AGame(void) = default;
            ~AGame() = default;

            Arcade::gameState getState(void) const final override {return _state;};
            ssize_t getScore(void) const final override {return _score;};
            ssize_t getHighScore(void) const final override {return _highScore;};
            std::string getGameName(void) const final override {return _name;};
            void setIEvents(std::shared_ptr<Arcade::IEvent> event) final override {_event = event;};
            void setIDisplay(std::shared_ptr<Arcade::IDisplay> display) final override {_display = display;};

        protected:
            std::string _name;
            Arcade::gameState _state;
            ssize_t _score;
            ssize_t _highScore;
            std::shared_ptr<Arcade::IEvent> _event;
            std::shared_ptr<Arcade::IDisplay> _display;
    };
}