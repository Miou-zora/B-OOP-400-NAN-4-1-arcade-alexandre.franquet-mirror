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
        IKEY_LEFT,
        IKEY_RIGHT,
        IKEY_SPACE,
        IKEY_ENTER,
        IKEY_BACKSPACE,
        IKEY_TAB,
        IKEY_SHIFT,
        IKEY_CTRL,
        IKEY_ALT,

        /* Globals inputs */
        IKEY_B, //Graphical library
        IKEY_D, //Game library
        IKEY_S, //QUIT
        IKEY_M, //MENU

        /*Those key are for arcade control Exit/Menu/... */
        IKEY_Q,
        IKEY_ESC,
        IKEY_A,
        IKEY_C,
        IKEY_E,
        IKEY_F,
        IKEY_G,
        IKEY_H,

        IKEY_I,
        IKEY_J,
        IKEY_K,
        IKEY_L,
        IKEY_N,
        IKEY_O,
        IKEY_P,
        IKEY_Q,
        IKEY_R,
        IKEY_T,
        IKEY_U,
        IKEY_V,
        IKEY_W,
        IKEY_X,
        IKEY_Y,
        IKEY_Z,
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