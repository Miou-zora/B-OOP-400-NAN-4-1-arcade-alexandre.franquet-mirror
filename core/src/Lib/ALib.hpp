/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** ALib
*/

#pragma once
#include "ILib.hpp"
#include "Types.hpp"
#include <unordered_map>

namespace Arcade {
    /**
     * @brief Abstract class for the graphical library
     */
    class ALib : virtual public Arcade::ILib {
        public:
            ALib(void) = default;
            ~ALib() = default;

            void setScale(std::pair<ssize_t, ssize_t> scale) final override { _scale = scale; }
            void setScale(ssize_t scale) final override { _scale = std::pair<ssize_t, ssize_t>(scale, scale); }
            void setSize(std::pair<ssize_t, ssize_t> size) final override { _size = size; }
            std::pair<ssize_t, ssize_t> getScale(void) const final override { return _scale; }
            std::pair<ssize_t, ssize_t> getSize(void) const final override { return _size; }

            bool isKeyPressed(Arcade::Inputs) override { return false; }
            bool isKeyReleased(Arcade::Inputs) override { return false; }

        private:
            /// @brief The scale of the window
            std::pair<ssize_t, ssize_t> _scale;
            /// @brief The size of the window
            std::pair<ssize_t, ssize_t> _size;

        protected:
            /// @brief The map of all key pressed or not
            std::unordered_map<Arcade::Inputs, bool> _keys;
            /// @brief The name of the library
            std::string _name;
    };
}
