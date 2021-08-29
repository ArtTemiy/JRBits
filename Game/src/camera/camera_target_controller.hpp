//
// Created by Artemiy Shvedov on 03.07.21.
//

#pragma once

#include <TopDownEngine/controller/controller.hpp>
#include <TopDownEngine/drawable/camera.hpp>

namespace Controllers {
    class CameraTargetController : public Engine::Controller::Controller<Engine::Drawable::Camera> {
        std::weak_ptr<Engine::Object> target_;

    public:
        void Tick(double time_delta) override;

        bool ProcessEvent(const sf::Event& event) override;

        const std::weak_ptr<Engine::Object>& GetTarget() const { return target_; }

        void SetTarget(const std::weak_ptr<Engine::Object>& target) { target_ = target; }
    };
} // namespace Controllers