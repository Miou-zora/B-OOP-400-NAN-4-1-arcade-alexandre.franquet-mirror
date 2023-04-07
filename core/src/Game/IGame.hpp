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

    /**
     * @brief Interface for one game library
     */
    class IGame {
        public:
            /**
             * @brief Construct a new IGame object
             */
            IGame(void) = default;

            /**
             * @brief Destroy the IGame object
             */
            virtual ~IGame() = default;

            /**
             * @brief Load the game
             * @details This function can load all the assets needed for the game or entities that will be used in the game.
             */
            virtual void load(void) = 0;

            /**
             * @brief Update the game
             * @details This function will be called every frame and will update the game.
             * @param lib graphical library, used to get inputs.
             * @param seconds time elapsed since the last frame.
             */
            virtual void update(Arcade::ILib &lib, float seconds) = 0;

            /**
             * @brief Render the game
             * @details This function will be called every frame and will render entities with grahical library.
             * @param lib graphical library, used to render entities.
             */
            virtual void render(Arcade::ILib &lib) = 0;

            /**
             * @brief Reset the game
             * @details This function will be called when the game is reset. It should reset all the entities to their initial state.
             */
            virtual void reset(void) = 0;

            /**
             * @brief Unload the game
             * @details This function will be called when the game is unloaded. It should unload all the assets and entities.
             */
            virtual void unload(void) = 0;

            /**
             * @brief Get the game state
             * @details This function will return the current state of the game.
             * @return The current state of the game.
             */
            virtual Arcade::gameState getState(void) const = 0;

            /**
             * @brief Get the game score
             * @details This function will return the current score of the game.
             * @return The current score of the game.
             */
            virtual ssize_t getScore(void) const = 0;

            /**
             * @brief Get the game high score
             * @details This function will return the current high score of the game.
             * @return The current high score of the game.
             */
            virtual ssize_t getHighScore(void) const = 0;

            /**
             * @brief Get the game name
             * @details This function will return the name of the game.
             * @return The name of the game.
             */
            virtual std::string getGameName(void) const = 0;
    };
};
