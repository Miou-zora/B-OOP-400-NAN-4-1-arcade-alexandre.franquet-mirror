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
    _isAlive = true;
    _score = 0;
    _highScore = 0;
    _size_snake = 4;
    _direction = RIGHT;
    _second = 0;
    _timeToUpdate = 0.1;
    _eating = false;
    _state = MENU;
    load();

}

void Arcade::SnakeGame::generateFood()
{
    int x = rand() % 19;
    int y = rand() % 19;

    if (_int_map[y][x] == EMPTY) {
        _int_map[y][x] = FOOD;
        std::shared_ptr<Arcade::AObject> food = std::make_shared<Arcade::AObject>();
        food->setShape(Arcade::Shapes::SQUARE);
        food->setPosition({30*x, 30*y});
        food->setSize({1*20, 1*20});
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
        moveFunction(0, -1, UP);
            break;
        case DOWN:
            moveFunction(0, 1, DOWN);
            break;
        case LEFT:
            moveFunction(-1, 0, LEFT);
            break;
        case RIGHT:
            moveFunction(1, 0, RIGHT);
            break;
        default:
            break;
    }
}

int Arcade::SnakeGame::moveFunction(int x, int y, int dir)
{
    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++) {
            if (_map[i][j] == 'S') {
                check_collisions(j+x, i+y);
                if (isEatingFood(j+x, i+y)) {
                    _foodObjects.clear();
                    generateFood();
                    _score += 1;
                    if (_score > _highScore)
                        _highScore = _score;
                    _eating = true;
                }
                if (_isAlive) {
                    _map[i][j] = 's';
                    _map[i +y][j+x] = 'S';
                    _int_map[i+y][j+x] = dir;
                    _int_map[i][j] = dir;
                    if (!_eating) {
                        delete_tail();
                    }
                    _eating = false;
                    return(0);
                }
            }
        }
    }
    return (0);
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

void Arcade::SnakeGame::updateMove(Arcade::ILib &lib)
{
    if (_second >= _timeToUpdate && _isAlive && _state == GAME) {
        if (lib.isKeyPressed(IKEY_SHIFT))
            _timeToUpdate = 0.18;
        else if (lib.isKeyPressed(IKEY_SPACE))
            _timeToUpdate = 0.06;
        else
            _timeToUpdate = 0.1;
        _snakeObjects.clear();
        move();
        generateSnake();
        _second -= _timeToUpdate;
    }
}

int Arcade::SnakeGame::checkWinGame()
{
    for (size_t y = 0; y < _int_map.size(); y++) {
        for (size_t x = 0; x < _int_map[y].size(); x++) {
            if (_int_map[y][x] == EMPTY || _int_map[y][x] == FOOD) {
                return(0);
            }
        }
    }
    _state = END;
    return(0);
}

void Arcade::SnakeGame::update(Arcade::ILib &lib, float milliseconds)
{
    _second += milliseconds;
    changeKeyDirection(lib);
    checkWinGame();

    if (_state == MENU && lib.isKeyPressed(IKEY_ENTER)) {
        _state = GAME;
        _second = 0;
    }

    if (_state == GAME) {
        updateMove(lib);
    }

    if (lib.isKeyPressed(IKEY_ESC)) {
        _state = PAUSE;
    }
    if (_state == PAUSE && lib.isKeyPressed(IKEY_ENTER)) {
        _state = GAME;
        _second = 0;
    }
    if (_state == PAUSE || _state == GAME || _state == END) {
        if (lib.isKeyPressed(IKEY_R)) {
            reset();
        }
    }
    if (!_isAlive) {
        std::ofstream file("highscore.txt");
        if (file.is_open()) {
            if (_highScore > _score) {
                file << _highScore;
            } else {
                file << _score;
            }
            file.close();
        }
    }
}

void Arcade::SnakeGame::reset()
{
    _mapObjects.clear();
    _snakeObjects.clear();
    _foodObjects.clear();
    _map.clear();
    _int_map.clear();
    _direction = RIGHT;
    _isAlive = true;
    _score = 0;
    _timeToUpdate = 0.1;
    _second = 0;
    _state = MENU;
    _eating = false;
    load();
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
                wall->setPosition({30*x, 30*y});
                wall->setSize({1*20, 1*20});
                wall->setColor(Arcade::Colors::RED);
                wall->setFilePath("");
                _mapObjects.push_back(wall);
            } else {
                std::shared_ptr<Arcade::AObject> empty = std::make_shared<Arcade::AObject>();
                empty->setShape(Arcade::Shapes::SQUARE);
                empty->setPosition({30*x, 30*y});
                empty->setSize({1*20, 1*20});
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
            if (_map[y][x] == 's' || _map[y][x] == '-') {
                std::shared_ptr<Arcade::AObject> snake = std::make_shared<Arcade::AObject>();
                snake->setShape(Arcade::Shapes::SQUARE);
                snake->setPosition({30*x, 30*y});
                snake->setSize({1*20, 1*20});
                snake->setColor(Arcade::Colors::BLUE);
                snake->setFilePath("");
                _snakeObjects.push_back(snake);
            }
            if (_map[y][x] == 'S') {
                std::shared_ptr<Arcade::AObject> snake = std::make_shared<Arcade::AObject>();
                snake->setShape(Arcade::Shapes::SQUARE);
                snake->setPosition({30*x, 30*y});
                snake->setSize({1*20, 1*20});
                snake->setColor(Arcade::Colors::MAGENTA);
                snake->setFilePath("");
                _snakeObjects.push_back(snake);
            }
        }
    }
}

void Arcade::SnakeGame::loadHighScore()
{
    std::ifstream file("highscore.txt");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (std::stoi(line) > _highScore)
            _highScore = std::stoi(line);
        }
        file.close();
    } else {
        std::ofstream newFile("highscore.txt");
        if (newFile.is_open()) {
            newFile << _highScore;
            newFile.close();
        }
    }
}

void Arcade::SnakeGame::load(void)
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
    fill_tab_int();
    generateMap();
    generateSnake();
    generateFood();
    loadHighScore();
}

void Arcade::SnakeGame::displayPause(Arcade::ILib &lib)
{
    for (auto &object : _mapObjects) {
            lib.drawObjets(object);
        }
    lib.drawObjets(*_foodObjects.begin());
    for (auto &object : _snakeObjects)
        lib.drawObjets(object);
    lib.drawText(std::string("Score : " + std::to_string(_score)), WHITE, 1, {20,0});
    lib.drawText(std::string("Pause"), WHITE, 3*20, {5*30, 5*30});
    lib.drawText(std::string("Press Enter to continue"), WHITE, 2*20, {1*30, 10*30});
}

void Arcade::SnakeGame::render(Arcade::ILib &lib)
{
    if (_state == END) {
        lib.drawText(std::string("You Win "), WHITE, 3*20, {3*30, 5*30});
        lib.drawText(std::string("Press Enter to start"), WHITE, 2*20, {1*30, 10*30});
    }

    if (_state == GAME) {
        for (auto &object : _mapObjects) {
            lib.drawObjets(object);
        }
        lib.drawObjets(*_foodObjects.begin());
        for (auto &object : _snakeObjects)
            lib.drawObjets(object);
        lib.drawText(std::string("Score : " + std::to_string(_score)), WHITE, 1*20, {20*30,0*30});
        lib.drawText(std::string("Highscore : " + std::to_string(_highScore)), WHITE, 1*20, {20*30,1*30});
    }

    if (_state == MENU) {
        lib.drawText(std::string("Snake"), YELLOW, 3*20, {5*30, 5*30});
        lib.drawText(std::string("Press Enter to start"), YELLOW, 2*20, {1*30, 10*30});
    }

    if (_state == PAUSE) {
        displayPause(lib);
    }
    if (!_isAlive) {
        lib.drawText(std::string("Game Over"), YELLOW, 3*20, {3*30, 5*30});
        lib.drawText(std::string("Press R to restart"), YELLOW, 3*20, {1*30, 10*30});
    }
}
