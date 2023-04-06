/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-alexandre.franquet-mirror
** File description:
** snake
*/

#include "snake.hpp"
#include <iostream>
#include <unistd.h>

extern "C"
{
    Arcade::IGame *GameEntryPoint()
    {
        return new Arcade::SnakeGame();
    }
}

void Arcade::SnakeGame::fill_tab_int()
{
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 's' || _map[y][x] == 'S' || _map[y][x] == '-') {
                _int_map[y][x] = 1;
            }
            else if (_map[y][x] == ' ') {
                _int_map[y][x] = 0;
            }
            else if (_map[y][x] == '#') {
                _int_map[y][x] = -1;
            }
        }
    }
}

void print_tab(std::vector<std::vector<int>> map)
{
    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].size(); x++) {
            std::cout << map[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

Arcade::SnakeGame::SnakeGame(void)
{
    _map = {
        "####################",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#  -ssS            #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "####################"
    };
    _snake = {"-ssS"};
    _food = "f";
    _int_map = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };

    fill_tab_int();
}

int Arcade::SnakeGame::findValHead()
{
    for (size_t y = 0; y < _int_map.size(); y++) {
        for(size_t x = 0; x < _int_map[y].size(); x++) {
            if (_map[y][x] == 'S') {
                return (_int_map[y][x]);
            }
        }
    }
    return (0);
}

Arcade::SnakeGame::~SnakeGame()
{
}

void Arcade::SnakeGame::moveSnake()
{

    switch (_direction) {
        case UP:
            moveSnakeUp();
            break;
        case DOWN:
            moveSnakeDown();
            break;
        case LEFT:
            moveSnakeLeft();
            break;
        case RIGHT:
            moveSnakeRight();
            break;
        default:
            break;
    }
}

void Arcade::SnakeGame::moveSnakeUp()
{
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 'S') {
                check_collisions(x, y-1);
                if (_isAlive) {
                    _map[y][x] = 's';
                    _map[y-1][x] = 'S';
                    _int_map[y-1][x] = UP;
                    _int_map[y][x] = UP;
                    break;
                }
            }
        }
    }
    change_tail();
}

int  Arcade::SnakeGame::moveSnakeDown()
{
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 'S') {
                check_collisions(x, y+1);
                if (_isAlive) {
                    _map[y][x] = 's';
                    _map[y+1][x] = 'S';
                    _int_map[y+1][x] = DOWN;
                    _int_map[y][x] = DOWN;
                    change_tail();
                    return(0);
                }
            }
        }
    }
    return (0);
}

void Arcade::SnakeGame::moveSnakeLeft()
{
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 'S') {
                check_collisions(x-1, y);
                if (_isAlive) {
                    _map[y][x] = 's';
                    _map[y][x-1] = 'S';
                    _int_map[y][x-1] = LEFT;
                    _int_map[y][x] = LEFT;
                    break;
                }
            }
        }
    }
    change_tail();
}

int Arcade::SnakeGame::change_tail(void)
{
    if (!_isAlive) {
        return (0);
    }
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == '-') {
                switch (_int_map[y][x])
                {
                case UP :
                    _map[y][x] = ' ';
                    _int_map[y][x] = 0;
                    _map[y-1][x] = '-';
                    break;
                case DOWN :
                    _map[y][x] = ' ';
                    _int_map[y][x] = 0;
                    _map[y+1][x] = '-';
                    return(0);
                    break;
                case LEFT :
                    _map[y][x] = ' ';
                    _int_map[y][x] = 0;
                    _map[y][x-1] = '-';
                    break;
                case RIGHT :
                    _map[y][x] = ' ';
                    _int_map[y][x] = 0;
                    _map[y][x+1] = '-';
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }
    return (0);
}

void Arcade::SnakeGame::moveSnakeRight()
{
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 'S') {
                check_collisions(x+1, y);
                if (_isAlive) {
                    _map[y][x] = 's';
                    _int_map[y][x] = RIGHT;
                    _map[y][x+1] = 'S';
                    _int_map[y][x+1] = RIGHT;
                    break;
                }
            }
        }
    }
    change_tail();
}

void Arcade::SnakeGame::changeKeyDirection(Arcade::ILib &lib)
{
    if (lib.isKeyPressed(Arcade::IKEY_UP) && findValHead() != DOWN)
        _direction = UP;
    if (lib.isKeyPressed( Arcade::IKEY_DOWN) && findValHead() != UP)
        _direction = DOWN;
    if (lib.isKeyPressed( Arcade::IKEY_LEFT) && findValHead() != RIGHT)
        _direction = LEFT;
    if (lib.isKeyPressed( Arcade::IKEY_RIGHT) && findValHead() != LEFT)
        _direction = RIGHT;
}

void Arcade::SnakeGame::move()
{
    moveSnake();

}

void Arcade::SnakeGame::check_collisions(int x, int y)
{
    if (_int_map[y][x] == -1 || _int_map[y][x] > 0) {
        _isAlive = false;
    }
}

void Arcade::SnakeGame::update(Arcade::ILib &lib, float milliseconds)
{
    generateMap();
    generateSnake();

    _second += milliseconds/1000;

    if (_second >= _timeToUpdate && _isAlive) {
        _allObjects.clear();
        move();
        changeKeyDirection(lib);
        generateSnake();
        _second -= _timeToUpdate;
    }
    (void) lib;
}

void Arcade::SnakeGame::reset()
{
}

void Arcade::SnakeGame::unload()
{
}

void Arcade::SnakeGame::generateMap(void)
{
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == '#') {
                std::shared_ptr<Arcade::AObject> wall = std::make_shared<Arcade::AObject>();
                wall->setShape(Arcade::Shapes::SQUARE);
                wall->setPosition({50*x + 450, 50*y});
                wall->setSize({50, 50});
                wall->setColor(Arcade::Colors::RED);
                wall->setFilePath("");
                _allObjects.push_back(wall);
            }
            if (_map[y][x] == ' ') {
                std::shared_ptr<Arcade::AObject> empty = std::make_shared<Arcade::AObject>();
                empty->setShape(Arcade::Shapes::SQUARE);
                empty->setPosition({50*x+450, 50*y});
                empty->setSize({50, 50});
                empty->setColor(Arcade::Colors::GREEN);
                empty->setFilePath("");
                _allObjects.push_back(empty);
            }
        }
    }
}

void Arcade::SnakeGame::generateSnake(void)
{
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 'S' || _map[y][x] == 's' || _map[y][x] == '-') {
                std::shared_ptr<Arcade::AObject> snake = std::make_shared<Arcade::AObject>();
                snake->setShape(Arcade::Shapes::SQUARE);
                snake->setPosition({50*x+450, 50*y});
                snake->setSize({50, 50});
                snake->setColor(Arcade::Colors::BLUE);
                snake->setFilePath("");
                _allObjects.push_back(snake);
            }
        }
    }
}

void Arcade::SnakeGame::load(void)
{
    generateMap();
    generateSnake();
}

void Arcade::SnakeGame::render(Arcade::ILib &lib)
{
    for (auto &object : _allObjects) {
        lib.drawObjets(object);
    }
}
