//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include "controller.hpp"

#include <unordered_map>

namespace Engine::Controller {

    /// Controller for player character
    /// Processes moving and moves object
    class PlayerController : public IController {
    public:
        /// Possible actions
        enum Actions {
            kGoUp,
            kGoDown,
            kGoRight,
            kGoLeft,
            kWin
        };

    private:
    public:
        explicit PlayerController(DynamicObject &object);

    private:

        /// Key bindings for actions
        static std::unordered_map<sf::Keyboard::Key, Actions> key_bindings;

        /// actions bindings to moving directions
        static const std::unordered_map<Actions, MovingDirection> moving_directions;

    public:
        /// Process input from keyboard and mouse
        bool ProcessEvent(const sf::Event &event) override;

        void Tick(double time_delta) override {}
    };
}