/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** Types
*/

#pragma once

namespace Arcade {

    enum Shapes {
        SQUARE,
        CIRCLE,
        TRIANGLE,
        NO_SHAPE
    };

    enum Inputs {
        /*Those are for in game inputs for player movement */
        IKEY_UP,
        IKEY_DOWN,
        IKEY_LEFT,
        IKEY_RIGHT,
        IKEY_SPACE,

        /*Those key are for arcade control Exit/Menu/... */
        IKEY_Q,
        IKEY_ESC,
        IKEY_G,
        IKEY_H,

        NO_KEY
    };

    enum Colors {
        BLACK,
        WHITE,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        MAGENTA,
        CYAN,
        TRANSPARENT,
        NO_COLOR
    };
}