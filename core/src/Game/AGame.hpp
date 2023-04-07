/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** AGame
*/

#pragma once
#include "IGame.hpp"

namespace Arcade
{
    /**
     *  @brief Abstract class for the game
     **/
    class AGame : virtual public Arcade::IGame {
        public:
            AGame(void) = default;
            ~AGame() = default;

            Arcade::gameState getState(void) const final override {return _state;};
            ssize_t getScore(void) const final override {return _score;};
            ssize_t getHighScore(void) const final override {return _highScore;};
            std::string getGameName(void) const final override {return _name;};

        protected:
            /// @brief The name of the game
            std::string _name;
            /// @brief The actual state of the game
            Arcade::gameState _state;
            /// @brief The actual score of the game
            ssize_t _score;
            /// @brief The high score of the game
            ssize_t _highScore;
    };
}
