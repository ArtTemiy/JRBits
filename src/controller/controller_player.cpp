//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/controller/controller_player.hpp>

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
        switch (event.type) {
            case sf::Event::KeyPressed:
                if (key_bindings.find(event.key.code) != key_bindings.end()) {
                    RunActionKeyPressed(key_bindings[event.key.code]);
                    return true;
                }
            case sf::Event::KeyReleased:
                if (key_bindings.find(event.key.code) != key_bindings.end()) {
                    RunActionKeyReleased(key_bindings[event.key.code]);
                    return true;
                }
            default:
                return false;
        }
    }

    void PlayerController::RunActionKeyPressed(PlayerController::Actions action) {
        switch (action) {
            case kGoUp:
            case kGoDown:
            case kGoRight:
            case kGoLeft:
                object_ptr_->AddMovingDirection(moving_directions.at(action));
                break;
            case kWin:
                LOG(INFO) << "You win.";
                break;
        }
    }

    void PlayerController::RunActionKeyReleased(PlayerController::Actions action) {
        switch (action) {
            case kGoUp:
            case kGoDown:
            case kGoRight:
            case kGoLeft:
                object_ptr_->AddMovingDirection(-moving_directions.at(action));
                break;
            default:
                break;
        }
    }
}
