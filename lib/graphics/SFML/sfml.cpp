/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-alexandre.franquet-mirror
** File description:
** sfml
*/

#include "sfml.hpp"
#include <iostream>

extern "C"
{
    Arcade::ILib *DisplayEntryPoint()
    {
        return new Arcade::SfmlLib();
    }
}

Arcade::SfmlLib::~SfmlLib() {
    if (_window.isOpen())
        _window.close();
};

bool Arcade::SfmlLib::isWindowClosed(void)
{
    return !_window.isOpen();
}

void Arcade::SfmlLib::updateEvent(void) {
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _keys[Arcade::Inputs::IKEY_Q] = true;
        if (_keyMap.count(_event.key.code)) {
            if (_event.type == sf::Event::KeyPressed) {
                    _keys[_keyMap[_event.key.code]] = true;
            }
            if (_event.type == sf::Event::KeyReleased) {
                    _keys[_keyMap[_event.key.code]] = false;
            }
        }
    }
}

bool Arcade::SfmlLib::isKeyPressed(Arcade::Inputs input)
{
    return _keys[input];
}

bool Arcade::SfmlLib::isKeyReleased(Arcade::Inputs input)
{
    return !_keys[input];
}


void Arcade::SfmlLib::createWindow(void)
{
    _window.create(sf::VideoMode(1920, 1080), "Arcade");
}

void Arcade::SfmlLib::closeWindow(void)
{
    _window.close();
}

void Arcade::SfmlLib::clearWindow(void)
{
    _window.clear();
}

void Arcade::SfmlLib::renderWindow(void)
{
    _window.display();
}

void Arcade::SfmlLib::drawObjets(std::shared_ptr<Arcade::IObject> object) {
    std::string fp = object->getFilePath();
    if (object->getFilePath().compare("") == 0) {
        drawShapes(object->getShape(), object->getColor(), object->getPosition(), object->getSize());
        return;
    }
    bool isTextured = _textures[fp].loadFromFile(object->getFilePath());
    _sprites[fp].setTexture(_textures[fp]);
    if (!isTextured) {
        _sprites[fp].setColor(arcadeColorToSfColor(object->getColor()));
    }
    _sprites[fp].setPosition(object->getPosition().first, object->getPosition().second);
    _sprites[fp].setScale(object->getSize().first, object->getSize().second);
    _window.draw(_sprites[fp]);
}

void Arcade::SfmlLib::drawShapes(Arcade::Shapes shape, Arcade::Colors color, std::pair<ssize_t, ssize_t> pos, std::pair<ssize_t, ssize_t> size) {
    std::unique_ptr<sf::Shape> sfShape = arcadeShapeToSfShape(shape, size);
    sfShape->setFillColor(arcadeColorToSfColor(color));
    sfShape->setPosition(pos.first, pos.second);
    _window.draw(*sfShape);
}

void Arcade::SfmlLib::drawText(std::shared_ptr<Arcade::Text> text) {
    if (_fonts.find("arial.ttf") == _fonts.end())
        _fonts["arial.ttf"].loadFromFile("./lib/graphics/SFML/arial.ttf");
    _texts[text->getText()].setFont(_fonts["arial.ttf"]);
    _texts[text->getText()].setString(text->getText());
    _texts[text->getText()].setCharacterSize(20);
    _texts[text->getText()].setFillColor(arcadeColorToSfColor(text->getColor()));
    _texts[text->getText()].setPosition(text->getPosition().first, text->getPosition().second);
    _window.draw(_texts[text->getText()]);
}

void Arcade::SfmlLib::drawText(std::string str, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> pos) {
    if (_fonts.find("arial.ttf") == _fonts.end())
        _fonts["arial.ttf"].loadFromFile("./lib/graphics/arial.ttf");
    _texts[str].setFont(_fonts["arial.ttf"]);
    _texts[str].setString(str);
    _texts[str].setCharacterSize(size);
    _texts[str].setFillColor(arcadeColorToSfColor(color));
    _texts[str].setPosition(pos.first, pos.second);
    _window.draw(_texts[str]);
}

sf::Color Arcade::SfmlLib::arcadeColorToSfColor(Arcade::Colors color) {
    switch (color) {
        case Arcade::Colors::BLACK:
            return sf::Color::Black;
        case Arcade::Colors::WHITE:
            return sf::Color::White;
        case Arcade::Colors::RED:
            return sf::Color::Red;
        case Arcade::Colors::GREEN:
            return sf::Color::Green;
        case Arcade::Colors::BLUE:
            return sf::Color::Blue;
        case Arcade::Colors::YELLOW:
            return sf::Color::Yellow;
        case Arcade::Colors::MAGENTA:
            return sf::Color::Magenta;
        case Arcade::Colors::CYAN:
            return sf::Color::Cyan;
        case Arcade::Colors::TRANSPARENT:
            return sf::Color::Transparent;
        default:
            return sf::Color::Black;
    };
}

std::unique_ptr<sf::Shape> Arcade::SfmlLib::arcadeShapeToSfShape(Arcade::Shapes shape, std::pair<ssize_t, ssize_t> size) {
    switch (shape) {
        case Arcade::Shapes::CIRCLE:
            return std::make_unique<sf::CircleShape>(sf::CircleShape(size.first));
        case Arcade::Shapes::SQUARE:
            return std::make_unique<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f(size.first, size.second)));
        case Arcade::Shapes::TRIANGLE:
            return std::make_unique<sf::CircleShape>(sf::CircleShape(size.first, 3));
        default:
            return std::make_unique<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f(size.first, size.second)));
    };
}
