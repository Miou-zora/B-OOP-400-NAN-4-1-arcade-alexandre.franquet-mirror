/*
** EPITECH PROJECT, 2023
** arcade-archi
** File description:
** IText
*/

#pragma once
#include <string>
#include <utility>
#include "Types.hpp"


namespace Arcade {

    class Text {

        /**
         * @brief The class Text is the generic way to handle text
        **/

        public:
            Text(void);
            Text(std::string, std::pair<ssize_t, ssize_t>, Arcade::Colors);
            ~Text();

            std::string getText(void) const { return _text;};
            void setText(std::string) { _text = _text; };
            std::pair<ssize_t, ssize_t> getPosition(void) const { return _position; };
            void setPosition(std::pair<ssize_t, ssize_t>) { _position = _position; };
            void setColor(Arcade::Colors) { _color = _color; };
            Arcade::Colors getColor(void) const { return _color; };

        private:
            std::string _text;
            std::pair<ssize_t, ssize_t> _position;
            Arcade::Colors _color;
    };
};
