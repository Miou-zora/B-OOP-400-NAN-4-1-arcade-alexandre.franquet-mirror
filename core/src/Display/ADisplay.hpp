/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** ADisplay
*/

#pragma once
#include "IDisplay.hpp"
#include "IObject.hpp"

namespace Arcade {
    class ADisplay : virtual public Arcade::IDisplay {
        /**
        *  @brief The class ADisplay is the abstract class of the Display
        *  @details The methods are overriden but useless in this class
        *  @details But the attributes are used in the inherited classes
        **/

        public:
            ADisplay(void) = default;
            ~ADisplay() = default;

            void setScale(std::pair<ssize_t, ssize_t> scale) final override {_scale = scale;};
            void setSize(std::pair<ssize_t, ssize_t> size) final override {_size = size;};
            std::pair<ssize_t, ssize_t> getScale(void) const final override {return _scale;};
            std::pair<ssize_t, ssize_t> getSize(void) const final override {return _size;};

        protected:
            std::pair<ssize_t, ssize_t> _scale;
            std::pair<ssize_t, ssize_t> _size;
    };
}