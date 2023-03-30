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

    /*Shapes for the IObjects */

    class IObject {

        /**
         * @brief The class IObject is the interface of the Objects
         * @details The methods are pure virtual and must be overriden in the inherited classes
         **/

        public:
            IObject(void) = default;
            virtual ~IObject() = default;

            virtual Arcade::Shapes getShape(void) const = 0;
            virtual void setShape(Arcade::Shapes) = 0;

            virtual std::pair<ssize_t, ssize_t> getPosition(void) const = 0;
            virtual void setPosition(std::pair<ssize_t, ssize_t>) = 0;

            virtual std::pair<ssize_t, ssize_t> getSize(void) const = 0;
            virtual void setSize(std::pair<ssize_t, ssize_t>) = 0;

            virtual void setColor(Arcade::Colors) = 0;
            virtual Arcade::Colors getColor(void) const = 0;

            virtual std::string getFilePath(void) const = 0;
            virtual void setFilePath(std::string) = 0;
    };
};
