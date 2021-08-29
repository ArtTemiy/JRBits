//
// Created by Artemiy Shvedov on 03.07.21.
//

#include "camera_target_controller.hpp"

namespace Controllers {
    void CameraTargetController::Tick(double time_delta) {
        if (!target_.expired()) {
            object_->SetCoordinates(target_.lock()->GetCoordinates());
        }
    }

    bool CameraTargetController::ProcessEvent(const sf::Event& event) {
        return false;
    }
} // namespace Controllers