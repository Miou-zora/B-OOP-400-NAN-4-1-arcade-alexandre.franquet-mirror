/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-alexandre.franquet-mirror
** File description:
** sfml
*/

#include "sfml.hpp"

extern "C"
{
    Arcade::ILib *DisplayEntryPoint()
    {
        return new Arcade::SfmlLib();
    }
}
