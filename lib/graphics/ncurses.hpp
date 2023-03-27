/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** ncurses
*/

#pragma once
#include <ncurses.h>
#include "ADisplay.hpp"
#include "IObject.hpp"

namespace Arcade {

    class NcursesDisplay : virtual public Arcade::ADisplay {

        /**
         *  @brief The class NcursesDisplay is the class that manages the display with the Ncurses library
         *  @details It can't use sprite but will use instead the Arcade::Shape and Arcade::Color
         */

        public:
            NcursesDisplay(void) final;
            ~NcursesDisplay() override final;

            void createWindow(void) override final;
            void closeWindow(void) override final;
            void clearWindow(void) override final;
            void renderWindow(void) override final;
            void drawObjets(Arcade::IObjets) override final;
            void drawText(Arcade::Text) {} override final;
            unsigned int setScale(void) {} override final;
            unsigned int setPosition(void) {} override final;

        private:
            WINDOW *_window;
    };
}
