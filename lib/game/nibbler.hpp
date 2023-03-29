/*
** EPITECH PROJECT, 2023
** B-OOP-400-NAN-4-1-arcade-architecture
** File description:
** nibbler
*/

#pragma once
#include "AGame.hpp"
#include "IObject.hpp"
#include <memory>
#include <vector>

namespace Arcade {

    class NibblerGame : public virtual AGame {
        /**
         *  @brief The class AGame is the abstract class of the Game
         *  @details The methods are overriden but useless in this class
         *  @details But the attributes are used in the inherited classes
         **/

        public:
            NibblerGame(void);
            ~NibblerGame();

            void load(void) final override;
            void update(Arcade::ILib &lib, float seconds) final override;
            void render(Arcade::ILib &lib) final override;
            void reset(void) final override;
            void unload(void) final override;

        private:
            std::vector<std::shared_ptr<Arcade::IObject>> _objects;
    };
}