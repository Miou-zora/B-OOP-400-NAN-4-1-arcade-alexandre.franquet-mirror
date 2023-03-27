/*
** EPITECH PROJECT, 2023
** arcade-archi
** File description:
** IDisplay
*/

#pragma once

#include "IObject.hpp"
#include "Text.hpp"
#include <memory>

namespace Arcade {
    class IDisplay {
        /**
         * @brief The class IDisplay is the interface of the Display
         * @details The methods are pure virtual and must be overriden in the inherited classes
        **/

        public:
            IDisplay(void) = default;
            virtual ~IDisplay() = default;

            virtual void createWindow(void) = 0;
            virtual void closeWindow(void) = 0;
            virtual void clearWindow(void) = 0;
            virtual void renderWindow(void) = 0;

            virtual void drawObjets(std::shared_ptr<Arcade::IObject>) = 0;
            virtual void drawShapes(Arcade::Shapes, Arcade::Colors, std::pair<ssize_t, ssize_t>, std::pair<ssize_t, ssize_t>) = 0;
            virtual void drawText(std::shared_ptr<Arcade::Text>) = 0;
            virtual void drawText(std::string, Arcade::Colors, ssize_t size, std::pair<ssize_t, ssize_t>) = 0;

            virtual void setScale(std::pair<ssize_t, ssize_t>) = 0;
            virtual void setSize(std::pair<ssize_t, ssize_t>) = 0;

            virtual std::pair<ssize_t, ssize_t> getScale(void) const = 0;
            virtual std::pair<ssize_t, ssize_t> getSize(void) const = 0;
    };
};
