//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/controller/player_controller.hpp>

#include <glog/logging.h>

namespace Engine::Controller {
    const std::unordered_map<PlayerController::Actions, MovingDirection> PlayerController::moving_directions = {
            {kGoUp, {-1, 0}},
            {kGoDown, {1, 0}},
            {kGoLeft, {0, -1}},
            {kGoRight, {0, 1}}
    };

    std::unordered_map<sf::Keyboard::Key, PlayerController::Actions> PlayerController::key_bindings = {
            {sf::Keyboard::W, kGoUp},
            {sf::Keyboard::S, kGoDown},
            {sf::Keyboard::A, kGoLeft},
            {sf::Keyboard::D, kGoRight}
    };

    bool PlayerController::ProcessEvent(const sf::Event &event) {
        // moving part
        object_ptr_->SetMovingDirection({0, 0});
        for (auto& [key, direction] : key_bindings) {
            if (moving_directions.find(direction) != moving_directions.end() &&
                sf::Keyboard::isKeyPressed(key)) {
                object_ptr_->AddMovingDirection(moving_directions.at(direction));
            }
        }

        // sf::Event
        switch (event.type) {
            default:
                return false;
        }
    }
}
