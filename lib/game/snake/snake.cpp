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
                _int_map[y][x] = EMPTY;
            }
            else if (_map[y][x] == '#') {
                _int_map[y][x] = WALL;
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
    _food = 'f';
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
    _isAlive = true;
    _score = 0;
    _highScore = 0;
    _size_snake = 4;
    _direction = RIGHT;
    _second = 0;
    _timeToUpdate = 0.1;

    fill_tab_int();

}

void Arcade::SnakeGame::generateFood()
{
    int x = rand() % 19;
    int y = rand() % 19;

    if (_int_map[y][x] == EMPTY) {
        _int_map[y][x] = FOOD;
        std::shared_ptr<Arcade::AObject> food = std::make_shared<Arcade::AObject>();
        food->setShape(Arcade::Shapes::SQUARE);
        food->setPosition({x, y});
        food->setSize({1, 1});
        food->setColor(Arcade::Colors::WHITE);
        food->setFilePath("");
        _foodObjects.push_back(food);
    }
    else {
        generateFood();
    }
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
                if (isEatingFood(x, y-1) == true) {
                    _foodObjects.clear();
                    generateFood();
                    _score += 10;
                }
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
    delete_tail();
}

int  Arcade::SnakeGame::moveSnakeDown()
{
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 'S') {
                check_collisions(x, y+1);
                if (isEatingFood(x, y+1) == true) {
                    _foodObjects.clear();
                    generateFood();
                    _score += 10;
                }
                if (_isAlive) {
                    _map[y][x] = 's';
                    _map[y+1][x] = 'S';
                    _int_map[y+1][x] = DOWN;
                    _int_map[y][x] = DOWN;
                    delete_tail();
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
                if (isEatingFood(x-1, y) == true) {
                    _foodObjects.clear();
                    generateFood();
                    _score += 10;
                }
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
    delete_tail();
}

int Arcade::SnakeGame::delete_tail(void)
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
                    _int_map[y][x] = EMPTY;
                    _map[y-1][x] = '-';
                    break;
                case DOWN :
                    _map[y][x] = ' ';
                    _int_map[y][x] = EMPTY;
                    _map[y+1][x] = '-';
                    return(0);
                    break;
                case LEFT :
                    _map[y][x] = ' ';
                    _int_map[y][x] = EMPTY;
                    _map[y][x-1] = '-';
                    break;
                case RIGHT :
                    _map[y][x] = ' ';
                    _int_map[y][x] = EMPTY;
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
                if (isEatingFood(x+1, y) == true) {
                    _foodObjects.clear();
                    generateFood();
                    _score += 10;
                }
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
    delete_tail();
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
    if (_int_map[y][x] == WALL || _int_map[y][x] > EMPTY) {
        _isAlive = false;
    }
}

bool Arcade::SnakeGame::isEatingFood(int x, int y)
{
    if (_int_map[y][x] == FOOD) {
        return (true);
    }
    return (false);
}

void Arcade::SnakeGame::update(Arcade::ILib &lib, float milliseconds)
{
    generateSnake();

    _second += milliseconds/1000;

    if (_second >= _timeToUpdate && _isAlive) {
        _snakeObjects.clear();
        move();
        changeKeyDirection(lib);
        generateSnake();
        _second -= _timeToUpdate;
    }
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
                wall->setPosition({x, y});
                wall->setSize({1, 1});
                wall->setColor(Arcade::Colors::RED);
                wall->setFilePath("");
                _mapObjects.push_back(wall);
            } else {
                std::shared_ptr<Arcade::AObject> empty = std::make_shared<Arcade::AObject>();
                empty->setShape(Arcade::Shapes::SQUARE);
                empty->setPosition({x, y});
                empty->setSize({1, 1});
                empty->setColor(Arcade::Colors::GREEN);
                empty->setFilePath("");
                _mapObjects.push_back(empty);
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
                snake->setPosition({x, y});
                snake->setSize({1, 1});
                snake->setColor(Arcade::Colors::BLUE);
                snake->setFilePath("");
                _snakeObjects.push_back(snake);
            }
        }
    }
}

void Arcade::SnakeGame::load(void)
{
    generateMap();
    generateSnake();
    generateFood();
}

void Arcade::SnakeGame::render(Arcade::ILib &lib)
{

    for (auto &object : _mapObjects) {
        lib.drawObjets(object);
    }

    lib.drawObjets(*_foodObjects.begin());

    for (auto &object : _snakeObjects)
        lib.drawObjets(object);
}
