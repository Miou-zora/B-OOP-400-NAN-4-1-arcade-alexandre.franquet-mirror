/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** Snake
*/

#pragma once
#include "AGame.hpp"
#include "IObject.hpp"
#include "AObjects.hpp"
#include <memory>
#include <vector>

namespace Arcade {

    class SnakeGame : public virtual AGame {
        enum DIRECTION {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        /**
         *  @brief The class AGame is the abstract class of the Game
         *  @details The methods are overriden but useless in this class
         *  @details But the attributes are used in the inherited classes
         **/

        public:
            SnakeGame(void);
            ~SnakeGame();

            void load(void) final override;
            void update(Arcade::ILib &lib, float seconds) final override;
            void render(Arcade::ILib &lib) final override;
            void reset(void) final override;
            void unload(void) final override;

            void generateMap(void);

        private:
            std::vector<std::shared_ptr<Arcade::AObject>> _allObjects;
            std::vector<std::string> _map;
            std::vector<std::string> _snake;
            std::string _food;
            int _score = 0;
            int _highScore = 0;
            int _speed = 1;

    };
}