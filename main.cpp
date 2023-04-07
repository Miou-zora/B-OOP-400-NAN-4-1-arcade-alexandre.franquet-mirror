/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** main
*/

#include <iostream>
#include "core/src/Lib/ILib.hpp"
#include "core/src/Game/AGame.hpp"
#include "core/src/Object/AObjects.hpp"
#include "core/src/Text/Text.hpp"
#include "core/Core.hpp"
#include "core/LibLoader.hpp"
#include "lib/game/nibbler.hpp"

int main(int ac, char **argv)
{
    (void) argv;
    srand(time(0));

    if (ac != 2) {
        return (84);
    }
    Arcade::Core core(argv[1]);
    core.loop();
    return (0);
}
