/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** ILib
*/

#pragma once
#include "Types.hpp"
#include <memory>
#include "Text.hpp"
#include "IObject.hpp"

namespace Arcade {
    /**
     * @brief Interface for the graphical library
     */
    class ILib {
        public:
            /**
             * @brief Construct a new ILib object
             */
            ILib(void) = default;

            /**
             * @brief Destroy the ILib object
             */
            ~ILib() = default;

            /**
             * @brief Check if a key is pressed
             *
             * @param input The key to check
             *
             * @return true if the key is pressed, false otherwise
             */
            virtual bool isKeyPressed(Arcade::Inputs input) = 0;

            /**
             * @brief Check if a key is released
             *
             * @param input The key to check
             *
             * @return true if the key is released, false otherwise
             */
            virtual bool isKeyReleased(Arcade::Inputs input) = 0;

            /**
             * @brief Check if the window is closed
             *
             * @return true if the window is closed, false otherwise
             */
            virtual bool isWindowClosed(void) = 0;

            /**
             * @brief Update all entities in the window
             */
            virtual void updateEvent(void) = 0;

            /**
             * @brief Create the window and open it
             */
            virtual void createWindow(void) = 0;

            /**
             * @brief Close the window
             */
            virtual void closeWindow(void) = 0;

            /**
             * @brief Clear all entities in the window
             */
            virtual void clearWindow(void) = 0;

            /**
             * @brief Display all entities in the window
             */
            virtual void renderWindow(void) = 0;

            /**
             * @brief Draw an IObject in the window
             *
             * @param object The object to draw
             */
            virtual void drawObjets(std::shared_ptr<Arcade::IObject> object) = 0;
            /**
             * @brief Draw a shape in the window with a color, a position and a size
             *
             * @param shape The shape to draw
             * @param color The color of the shape
             * @param pos The position of the shape
             * @param size The size of the shape
             */
            virtual void drawShapes(Arcade::Shapes shape, Arcade::Colors color, std::pair<ssize_t, ssize_t> pos, std::pair<ssize_t, ssize_t> size) = 0;

            /**
             * @brief Draw a text in the window
             *
             * @param text The text to draw
             */
            virtual void drawText(std::shared_ptr<Arcade::Text> text) = 0;

            /**
             * @brief Draw a text in the window
             *
             * @param str The text to draw
             * @param color The color of the text
             * @param size The size of the text
             * @param pos The position of the text
             */
            virtual void drawText(std::string str, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> pos) = 0;

            /**
             * @brief Set the Scale of the window
             *
             * @param scale The scale to set
             */
            virtual void setScale(std::pair<ssize_t, ssize_t> scale) = 0;

            /**
             * @brief Set the Scale of the window
             *
             * @param scale The scale to set
             */
            virtual void setScale(ssize_t scale) = 0;

            /**
             * @brief Set the Size of the window
             *
             * @param size The size to set
             */
            virtual void setSize(std::pair<ssize_t, ssize_t> size) = 0;

            /**
             * @brief Get the Scale of the window
             *
             * @return std::pair<ssize_t, ssize_t>
             */
            virtual std::pair<ssize_t, ssize_t> getScale(void) const = 0;

            /**
             * @brief Get the Size of the window
             *
             * @return std::pair<ssize_t, ssize_t>
             */
            virtual std::pair<ssize_t, ssize_t> getSize(void) const = 0;
    };
}
