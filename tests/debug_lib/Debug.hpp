/*
** EPITECH PROJECT, 2023
** boostrap-arcade
** File description:
** DisplayModule
*/

#ifndef DISPLAYMODULE_HPP_
#define DISPLAYMODULE_HPP_

#include <iostream>
#include "../core/src/Display/IDisplay.hpp"
#include <unistd.h>

class DebugModule: public Arcade::IDisplay {
    public:
        DebugModule() {};
        ~DebugModule() {};

        void createWindow(void) { std::cout << "createWindow" << std::endl; };
        void closeWindow(void) { std::cout << "closeWindow" << std::endl; };
        void clearWindow(void) { std::cout << "clearWindow" << std::endl; };
        void renderWindow(void) { std::cout << "renderWindow" << std::endl; sleep(1); };

        void drawObjets(std::shared_ptr<Arcade::IObject>) { std::cout << "drawObjets" << std::endl; };
        void drawShapes(Arcade::Shapes, Arcade::Colors, std::pair<ssize_t, ssize_t>, std::pair<ssize_t, ssize_t>) { std::cout << "drawShapes" << std::endl; };
        void drawText(std::shared_ptr<Arcade::Text>) { std::cout << "drawText" << std::endl; };
        void drawText(std::string text, Arcade::Colors color, ssize_t size, std::pair<ssize_t, ssize_t> position) {(void)size; std::cout << "drawText: " << text << " color: " << color << " size: " << size << " position: " << position.first << position.second << std::endl; };

        void setScale(std::pair<ssize_t, ssize_t>) { std::cout << "setScale" << std::endl; };
        void setSize(std::pair<ssize_t, ssize_t>) { std::cout << "setSize" << std::endl; };

        std::pair<ssize_t, ssize_t> getScale(void) const { std::cout << "getScale" << std::endl; return std::pair<ssize_t, ssize_t>(0, 0);};
        std::pair<ssize_t, ssize_t> getSize(void) const { std::cout << "getSize" << std::endl; return std::pair<ssize_t, ssize_t>(0, 0);};

    protected:
    private:
        std::string _name;
};

#endif /* !DISPLAYMODULE_HPP_ */
