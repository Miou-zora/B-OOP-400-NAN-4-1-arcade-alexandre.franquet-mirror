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
            RIGHT=1,
            DOWN,
            LEFT,
            UP
        };
        enum MAP_COMPONENT {
            FOOD = -2,
            WALL,
            EMPTY,
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
            void generateSnake(void);
            void generateFood(void);
            void fill_tab_int(void);
            void updateMove(Arcade::ILib &lib);
            int findValHead(void);

            int delete_tail(void);
            void moveSnake(void);
            void changeKeyDirection(Arcade::ILib &lib);
            void move(void);
            int moveFunction(int x, int y, int dir);

            void check_collisions(int x, int y);
            bool isEatingFood(int x, int y);


        private:
            std::vector<std::shared_ptr<Arcade::AObject>> _mapObjects;
            std::vector<std::shared_ptr<Arcade::AObject>> _snakeObjects;
            std::vector<std::string> _map;
            std::vector<std::vector<int>> _int_map;
            std::vector<std::string> _snake;
            std::vector<std::shared_ptr<Arcade::AObject>> _foodObjects;
            std::shared_ptr<Arcade::Text> _scoreText;
            char _food;
            bool _isAlive;
            int _score;
            int _highScore;
            int _size_snake;
            int _direction;
            float _second;
            float _timeToUpdate;
            bool _eating;

    };
}