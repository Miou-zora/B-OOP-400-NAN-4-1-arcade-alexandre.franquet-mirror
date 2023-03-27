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
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_SPACE,

        /*Those key are for arcade control Exit/Menu/... */
        KEY_Q,
        KEY_ESC,
        KEY_G,
        KEY_H,

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