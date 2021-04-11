//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include "controller.hpp"

#include <unordered_map>

namespace Engine::Controller {
    class PlayerController : public IController {
    public:
        enum Actions {
            kGoUp,
            kGoDown,
            kGoRight,
            kGoLeft,
            kWin
        };

    private:
        static std::unordered_map<sf::Keyboard::Key, Actions> key_bindings;
        static const std::unordered_map<Actions, MovingDirection> moving_directions;

        void RunActionKeyPressed(Actions action);

        void RunActionKeyReleased(Actions action);

    public:
        PlayerController() {}

        bool ProcessEvent(const sf::Event &event) override;
    };
}