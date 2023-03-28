/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** main
*/

#include <iostream>
#include "core/src/Display/ADisplay.hpp"
#include "core/src/Game/AGame.hpp"
#include "core/src/Object/AObjects.hpp"
#include "core/src/Input/AEvent.hpp"
#include "core/src/Text/Text.hpp"
#include "core/Arcade.hpp"
#include "core/LibLoader.hpp"
#include "lib/game/nibbler.hpp"
#include "lib/game/snake.hpp"

int main(int ac, char **argv)
{
    (void) argv;

    if (ac != 2) {
        return (84);
    }
    Arcade::Core core(argv[1]);
    core.loop();
    return (0);
}