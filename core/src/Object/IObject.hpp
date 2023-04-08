/*
** EPITECH PROJECT, 2023
** arcade-archi
** File description:
** IObject
*/

#pragma once
#include <utility>
#include "Lib/Types.hpp"

namespace Arcade {

    /**
     * @brief Interface for the object
     * @details The methods are pure virtual and must be overriden in the inherited classes
     **/
    class IObject {
        public:
            /**
             * @brief Construct a new IObject object
             * @details It is used to draw something with graphical library
             */
            IObject(void) = default;

            /**
             * @brief Destroy the IObject object
             */
            virtual ~IObject() = default;

            /**
             * @brief Get the Shape object
             * @return Arcade::Shapes
             */
            virtual Arcade::Shapes getShape(void) const = 0;

            /**
             * @brief Set the Shape object
             * @param shape
             */
            virtual void setShape(Arcade::Shapes shape) = 0;

            /**
             * @brief Get the Position object
             * @return std::pair<ssize_t, ssize_t>
             */
            virtual std::pair<ssize_t, ssize_t> getPosition(void) const = 0;

            /**
             * @brief Set the Position object
             * @param position
             */
            virtual void setPosition(std::pair<ssize_t, ssize_t> position) = 0;

            /**
             * @brief Get the Size object
             * @return std::pair<ssize_t, ssize_t>
             */
            virtual std::pair<ssize_t, ssize_t> getSize(void) const = 0;

            /**
             * @brief Set the Size object
             * @param size
             */
            virtual void setSize(std::pair<ssize_t, ssize_t> size) = 0;

            /**
             * @brief Set the Color object
             * @param color
             */
            virtual void setColor(Arcade::Colors color) = 0;

            /**
             * @brief Get the Color object
             * @return Arcade::Colors
             */
            virtual Arcade::Colors getColor(void) const = 0;

            /**
             * @brief Get the Texture object
             * @return std::string
             */
            virtual std::string getFilePath(void) const = 0;

            /**
             * @brief Set the Texture object
             * @param texture
             */
            virtual void setFilePath(std::string texture) = 0;
    };
};
