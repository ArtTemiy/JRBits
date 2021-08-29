//
// Created by Artemiy Shvedov on 30.04.21.
//
#pragma once

#include <TopDownEngine/controller/controller.hpp>

namespace Engine::Controller {

    /// Simple controller what do nothing
    class NullController : public Controller<> {
    public:
        NullController() = default;

        /// Discards any event
        bool ProcessEvent(const sf::Event &event) override {
            return false;
        }

        void Tick(double time_delta) override {}
    };
}