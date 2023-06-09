/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-alexandre.franquet-mirror
** File description:
** snake
*/

#include "nibbler.hpp"
#include <iostream>
#include <unistd.h>

extern "C"
{
    Arcade::IGame *GameEntryPoint()
    {
        return new Arcade::NibblerGame();
    }
}

void Arcade::NibblerGame::fill_tab_int()
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
            if (_map[y][x] == 'f') {
                _int_map[y][x] = FOOD;
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

Arcade::NibblerGame::NibblerGame(void)
{
    _isAlive = true;
    _isCollWall = false;
    _score = 0;
    _highScore = 0;
    _size_snake = 4;
    _direction = RIGHT;
    _second = 0;
    _timeToUpdate = 0.1;
    _eating = false;
    _isCollWall = false;
    _state = MENU;
    load();

}

void Arcade::NibblerGame::generateFood()
{
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 'f') {
                std::shared_ptr<Arcade::AObject> food = std::make_shared<Arcade::AObject>();
                food->setShape(Arcade::Shapes::SQUARE);
                food->setPosition({30*x, 30*y});
                food->setSize({1*20, 1*20});
                food->setColor(Arcade::Colors::WHITE);
                food->setFilePath("");
                _foodObjects.push_back(food);
            }
        }
    }
}

int Arcade::NibblerGame::findValHead()
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


Arcade::NibblerGame::~NibblerGame()
{
}

void Arcade::NibblerGame::moveSnake()
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

bool Arcade::NibblerGame::moveFreeDir(int x, int y)
{
    if (_int_map[y-1][x] == EMPTY) {
        _direction = UP;
        _isCollWall = false;
        moveFunction(0, -1, UP);
        return (true);
    }
    if (_int_map[y+1][x] == EMPTY) {
        _direction = DOWN;
        _isCollWall = false;
        moveFunction(0, 1, DOWN);
        return (true);
    }
    if (_int_map[y][x-1] == EMPTY) {
        _direction = LEFT;
        _isCollWall = false;
        moveFunction(-1, 0, LEFT);
        return (true);
    }
    if (_int_map[y][x+1] == EMPTY) {
        _direction = RIGHT;
        _isCollWall = false;
        moveFunction(1, 0, RIGHT);
        return (true);
    }
    return false;
}

bool Arcade::NibblerGame::checkIfAutomaticMovePossible(int x, int y)
{
    int countLeftRight = 0;
    int countUpDown = 0;

    if ((_int_map[y-1][x] == EMPTY || _int_map[y-1][x] == FOOD) && _direction != UP)
        countUpDown++;
    if ((_int_map[y+1][x] == EMPTY || _int_map[y+1][x] == FOOD) && _direction != DOWN)
        countUpDown++;
    if ((_int_map[y][x-1] == EMPTY || _int_map[y][x-1] == FOOD) && _direction != LEFT)
        countLeftRight++;
    if ((_int_map[y][x+1] == EMPTY || _int_map[y][x+1] == FOOD) && _direction != RIGHT)
        countLeftRight++;
    if (countUpDown == 2 || countLeftRight == 2)
        return (false);
    else
        return (moveFreeDir(x, y));
}

void Arcade::NibblerGame::destroyFood(int x, int y)
{
    for (size_t i = 0; i < _foodObjects.size(); i++) {
        if (_foodObjects[i]->getPosition().first/30 == x && _foodObjects[i]->getPosition().second/30 == y) {
            _foodObjects.erase(_foodObjects.begin() + i);
        }
    }
}

int Arcade::NibblerGame::moveFunction(int x, int y, int dir)
{
    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++) {
            if (_map[i][j] == 'S') {
                check_collisions(j+x, i+y);
                if (_isCollWall && checkIfAutomaticMovePossible(j, i))
                    return (0);
                if (_isCollWall)
                    return (0);
                if (isEatingFood(j+x, i+y)) {
                    destroyFood(j+x, i+y);
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


int Arcade::NibblerGame::delete_tail(void)
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

std::pair<int,int> Arcade::NibblerGame::updateHeadPos()
{
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            if (_map[y][x] == 'S') {
                _headPos = {x, y};
            }
        }
    }
    return _headPos;
}

void Arcade::NibblerGame::changeKeyDirection(Arcade::ILib &lib)
{
    updateHeadPos();

    if (lib.isKeyPressed(Arcade::IKEY_UP) && findValHead() != DOWN) {
        if (_headPos.second - 1 != -1)
            _isCollWall = false;
        _direction = UP;
    }
    if (lib.isKeyPressed( Arcade::IKEY_DOWN) && findValHead() != UP){
        if (_headPos.second + 1 != -1)
            _isCollWall = false;
        _direction = DOWN;
    }
    if (lib.isKeyPressed( Arcade::IKEY_LEFT) && findValHead() != RIGHT){
        if (_headPos.first - 1 != -1)
            _isCollWall = false;
        _direction = LEFT;
    }
    if (lib.isKeyPressed(Arcade::IKEY_RIGHT) && findValHead() != LEFT) {
        if (_headPos.first + 1 != -1)
            _isCollWall = false;
        _direction = RIGHT;
    }

}

void Arcade::NibblerGame::move()
{
    if (!_isCollWall)
      moveSnake();

}

void Arcade::NibblerGame::check_collisions(int x, int y)
{
    if (_int_map[y][x] > EMPTY) {
        _isAlive = false;
    }
    if (_int_map[y][x] == WALL)
        _isCollWall = true;
}

bool Arcade::NibblerGame::isEatingFood(int x, int y)
{
    if (_int_map[y][x] == FOOD) {
        return (true);
    }
    return (false);
}

void Arcade::NibblerGame::updateMove(Arcade::ILib &lib)
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

int Arcade::NibblerGame::checkWinGame()
{
    for (size_t y = 0; y < _int_map.size(); y++) {
        for (size_t x = 0; x < _int_map[y].size(); x++) {
            if (_int_map[y][x] == FOOD) {
                return(0);
            }
        }
    }
    _state = END;
    return(0);
}

void Arcade::NibblerGame::update(Arcade::ILib &lib, float milliseconds)
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

void Arcade::NibblerGame::reset()
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

void Arcade::NibblerGame::unload()
{
}

void Arcade::NibblerGame::generateMap(void)
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

void Arcade::NibblerGame::generateSnake(void)
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

void Arcade::NibblerGame::loadHighScore()
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

void Arcade::NibblerGame::load(void)
{
    _map = {
        "####################",
        "#f                f#",
        "#  ###    f    ### #",
        "#   f    ###    f  #",
        "#        # #       #",
        "#        ###       #",
        "#  ###         ### #",
        "#  #f           f# #",
        "#  #             # #",
        "#  #    #####    # #",
        "#  #    #f f#    # #",
        "#  f    #   #    f #",
        "#   #f         f#  #",
        "#                  #",
        "#    ###     ###   #",
        "#     f#  f  #f    #",
        "#      #     #     #",
        "#                  #",
        "#f -ssS           f#",
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

void Arcade::NibblerGame::displayPause(Arcade::ILib &lib)
{
    for (auto &object : _mapObjects) {
            lib.drawObjets(object);
        }
    for (auto &food : _foodObjects)
        lib.drawObjets(food);
    for (auto &object : _snakeObjects)
        lib.drawObjets(object);
    lib.drawText(std::string("Score : " + std::to_string(_score)), WHITE, 1*20, {20*30,0*30});
    lib.drawText(std::string("Pause"), WHITE, 3*20, {5*30, 5*30});
    lib.drawText(std::string("Press Enter to continue"), WHITE, 2*20, {1*30, 10*30});
}

void Arcade::NibblerGame::render(Arcade::ILib &lib)
{
    if (!_isAlive) {
        lib.drawText(std::string("Game Over"), WHITE, 3*20, {3*30, 5*30});
        lib.drawText(std::string("Press R to restart"), WHITE, 2*20, {1*30, 10*30});
    }
    if (_state == END) {
        lib.drawText(std::string("You Win "), WHITE, 3*20, {3*30, 5*30});
        lib.drawText(std::string("Press Enter to start"), WHITE, 2*20, {1*30, 10*30});
    }

    if (_state == GAME && _isAlive) {

        for (auto &object : _mapObjects) {
            lib.drawObjets(object);
        }
        for (auto &food : _foodObjects)
            lib.drawObjets(food);
        for (auto &object : _snakeObjects)
            lib.drawObjets(object);
        lib.drawText(std::string("Score : " + std::to_string(_score)), WHITE, 1*20, {20*30,0*30});
        lib.drawText(std::string("Highscore : " + std::to_string(_highScore)), WHITE, 1*20, {20*30,1*30});
    }

    if (_state == MENU && _isAlive) {
        lib.drawText(std::string("Nibbler"), WHITE, 3*20, {5*30, 5*30});
        lib.drawText(std::string("Press Enter to start"), WHITE, 2*20, {1*30, 10*30});
    }

    if (_state == PAUSE && _isAlive) {
        displayPause(lib);
    }
}
