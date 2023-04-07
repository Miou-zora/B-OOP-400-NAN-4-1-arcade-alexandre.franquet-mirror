/*
** EPITECH PROJECT, 2023
** arcade-archi
** File description:
** IText
*/

#pragma once
#include <string>
#include <utility>
#include "Lib/Types.hpp"


namespace Arcade {

    /**
     * @brief The class Text is the generic way to handle text
    **/
    class Text {
        public:
            /**
             * @brief Construct a new Text object
             * @details The default constructor of the class Text
             * @details Must be implemented in the inherited classes
             */
            Text(void);

            /**
             * @brief Construct a new Text object
             * @details The constructor of the class Text
             * @details Must be implemented in the inherited classes
             * @param text The text to display
             * @param pos The position of the text
             * @param color The color of the text
             */
            Text(std::string text, std::pair<ssize_t, ssize_t> pos, Arcade::Colors color);

            /**
             * @brief Destroy the Text object
             */
            ~Text() = default;

            /**
             * @brief Get the Text object
             * @return std::string
             */
            std::string getText(void) const { return _text;};

            /**
             * @brief Set the Text object
             * @param text
             */
            void setText(std::string) { _text = _text; };

            /**
             * @brief Get the Position object
             * @return std::pair<ssize_t, ssize_t>
             */
            std::pair<ssize_t, ssize_t> getPosition(void) const { return _position; };

            /**
             * @brief Set the Position object
             * @param position
             */
            void setPosition(std::pair<ssize_t, ssize_t>) { _position = _position; };

            /**
             * @brief Get the Color object
             * @return Arcade::Colors
             */
            void setColor(Arcade::Colors) { _color = _color; };

            /**
             * @brief Set the Color object
             * @param color
             */
            Arcade::Colors getColor(void) const { return _color; };

        private:
            /// @brief The text to display
            std::string _text;
            /// @brief The position of the text
            std::pair<ssize_t, ssize_t> _position;
            /// @brief The color of the text
            Arcade::Colors _color;
    };
};
