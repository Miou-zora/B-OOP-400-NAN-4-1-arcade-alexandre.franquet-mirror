/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** AEvent
*/

#pragma once
#include "IEvent.hpp"
#include "Types.hpp"
#include <queue>

namespace Arcade
{
    class AEvent : virtual public Arcade::IEvent
    {
        /**
         *  @brief The class AEvent is the abstract class of the Event
         *  @details The methods are overriden but useless in this class
         *  @details But the attributes are used in the inherited classes
         **/

    public:
        AEvent(void) = default;
        ~AEvent() = default;

        bool isGameKeyPressed(Arcade::Inputs) override { return false; }
        bool isGameKeyReleased(Arcade::Inputs) override { return false; }
        bool isLibKeyPressed(Arcade::Inputs) override { return false; }
        bool isLibKeyReleased(Arcade::Inputs) override { return false; }

        Arcade::Inputs getGameKeyPressed(void) override { return Arcade::Inputs::NO_KEY; }
        Arcade::Inputs getGameKeyReleased(void) override { return Arcade::Inputs::NO_KEY; }
        Arcade::Inputs getLibKeyPressed(void) override { return Arcade::Inputs::NO_KEY; }
        Arcade::Inputs getLibKeyReleased(void) override { return Arcade::Inputs::NO_KEY; }


    protected:
        /*Queue based on FIFO for the events*/
        std::queue<Arcade::Inputs> _gameKeysPressed;
        std::queue<Arcade::Inputs> _gameKeyReleased;

        std::queue<Arcade::Inputs> _libKeysPressed;
        std::queue<Arcade::Inputs> _libKeyReleased;

    private:
    };
} // namespace Arcade
