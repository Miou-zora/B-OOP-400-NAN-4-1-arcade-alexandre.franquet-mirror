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
            std::pair<ssize_t, ssize_t> _scale;
            std::pair<ssize_t, ssize_t> _size;

        protected:
            std::unordered_map<Arcade::Inputs, bool> _keys;
            std::string _name;
    };
}
