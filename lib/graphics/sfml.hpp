/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** SfmlLib
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "../core/src/Lib/ALib.hpp"

namespace Arcade {
    class SfmlLib : virtual public Arcade::ALib {

        /**
         *  @brief The class SfmlDisplay is the class that manages the display with the SFML library
         *  @details It can use the sprite throug a dict made of std::string -> sf::Sprite
         */

        public:
            SfmlLib(void) = default;
            ~SfmlLib() {
                if (_window.isOpen())
                    _window.close();
            };

            bool isWindowClosed(void) { return _window.isOpen(); };
            void updateEvent(void) { /* TODO: this */ };
            void createWindow(void) { _window.create(sf::VideoMode(1920, 1080), "Arcade"); };
            void closeWindow(void) { _window.close(); };
            void clearWindow(void) { _window.clear(); };
            void renderWindow(void) { _window.display(); };
            void drawObjets(std::shared_ptr<Arcade::IObject> object) {
                std::string fp = object->getFilePath();
                bool isTextured = _textures[fp].loadFromFile(object->getFilePath());
                _sprites[fp].setTexture(_textures[fp]);
                if (!isTextured) {
                    _sprites[fp].setColor(arcadeColorToSfColor(object->getColor()));
                }
                _sprites[fp].setPosition(object->getPosition().first, object->getPosition().second);
                _sprites[fp].setScale(object->getSize().first, object->getSize().second);
                _window.draw(_sprites[fp]);
            };
            void drawShapes(Arcade::Shapes shape, Arcade::Colors color, std::pair<ssize_t, ssize_t> pos, std::pair<ssize_t, ssize_t> size) {
                std::unique_ptr<sf::Shape> sfShape = arcadeShapeToSfShape(shape);
                sfShape->setFillColor(arcadeColorToSfColor(color));
                sfShape->setPosition(pos.first, pos.second);
                sfShape->setScale(size.first, size.second);
                _window.draw(*sfShape);
            };
            void drawText(std::shared_ptr<Arcade::Text> text) { (void)text; /* TODO */ };
            void drawText(std::string str, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> pos) { (void)pos; (void)color; (void)size; (void)str;/* TODO */ };

        private:

            sf::Color arcadeColorToSfColor(Arcade::Colors color) {
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

            std::unique_ptr<sf::Shape> arcadeShapeToSfShape(Arcade::Shapes shape) {
                switch (shape) {
                    case Arcade::Shapes::CIRCLE:
                        return std::make_unique<sf::CircleShape>();
                    case Arcade::Shapes::SQUARE:
                        return std::make_unique<sf::RectangleShape>();
                    case Arcade::Shapes::TRIANGLE:
                        return std::make_unique<sf::ConvexShape>();
                    default:
                        return std::make_unique<sf::CircleShape>();
                };
            }

            sf::RenderWindow _window;
            std::map<std::string, sf::Texture> _textures;
            std::map<std::string, sf::Sprite> _sprites;
    };
}
