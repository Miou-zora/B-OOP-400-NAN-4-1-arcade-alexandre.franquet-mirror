/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** AObjects
*/

#pragma once
#include "IObject.hpp"
#include "Lib/Types.hpp"

namespace Arcade {
    /**
     * @brief Abstract class for every entities in games
     */
    class AObject : virtual public Arcade::IObject {
        public:
            AObject(void) = default;
            ~AObject() = default;

            Arcade::Shapes getShape(void) const final override {return _shape;};
            std::pair<ssize_t, ssize_t> getPosition(void) const final override {return _position;};
            std::pair<ssize_t, ssize_t> getSize(void) const final override {return _size;};
            Arcade::Colors getColor(void) const final override {return _color;};
            std::string getFilePath(void) const final override {return _texture;};

            void setShape(Arcade::Shapes shape) final override {_shape = shape;};
            void setPosition(std::pair<ssize_t, ssize_t> position) final override {_position = position;};
            void setSize(std::pair<ssize_t, ssize_t> size) final override {_size = size;};
            void setColor(Arcade::Colors color) final override {_color = color;};
            void setFilePath(std::string texture) final override {_texture = texture;};

        protected:
            /// @brief The shape of the object
            Arcade::Shapes _shape;
            /// @brief The position of the object
            std::pair<ssize_t, ssize_t> _position;
            /// @brief The size of the object
            std::pair<ssize_t, ssize_t> _size;
            /// @brief The color of the object
            Arcade::Colors _color;
            /// @brief The texture of the object
            std::string _texture;
    };
}
