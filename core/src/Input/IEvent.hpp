/*
** EPITECH PROJECT, 2023
** arcade-archi
** File description:
** IInput
*/

#pragma once

#include "Types.hpp"
namespace Arcade {

    class IEvent {
        /**
         * @brief The class IEvent is the interface of the Event
         * @details The methods are pure virtual and must be overriden in the inherited classes
         * @details The purpose of this is to get every  xxx::Event -> Arcade::Event
         **/
        public:
            IEvent(void) = default;
            ~IEvent() = default;

            virtual bool isGameKeyPressed(Arcade::Inputs) = 0;
            virtual bool isGameKeyReleased(Arcade::Inputs) = 0;
            virtual bool isLibKeyPressed(Arcade::Inputs) = 0;
            virtual bool isLibKeyReleased(Arcade::Inputs) = 0;
            virtual Arcade::Inputs getGameKeyPressed(void) = 0;
            virtual Arcade::Inputs getGameKeyReleased(void) = 0;
            virtual Arcade::Inputs getLibKeyPressed(void) = 0;
            virtual Arcade::Inputs getLibKeyReleased(void) = 0;
            virtual bool isWindowClosed(void) = 0;
            virtual bool updateEvent(void) = 0;

    };
};