//
// Created by Artemiy Shvedov on 30.04.21.
//
#pragma once

#include <TopDownEngine/object/dynamic_object.hpp>
#include <TopDownEngine/controller/controller.hpp>

#include <SFML/Graphics.hpp>
#include <utility>

namespace Engine::Drawable {
    /// Camera for world. Only objects that are inside camera borders
    /// will be drawn on the screen
    /// ICamera is a interface but defines all general fields and methods
    class Camera : public DynamicObject {
        /// Game window
        sf::RenderWindow* window_;
        /// View to set
        sf::View view_;

        Controller::ControllerPtr controller_;

    public:
        void LevelInit(sf::RenderWindow* window, const Coordinates& coordinates = {0, 0});

        sf::View& GetView() {
            return view_;
        }

        void UpdateView();

        void SetController(Controller::ControllerPtr controller) {
            controller_ = std::move(controller);
            controller_->SetControllable(this);
        }
        ::Engine::Controller::ControllerPtr GetController() { return controller_; }

        /// Draws sprite in given coordinates
        void DrawSprite(sf::Sprite& sprite);

        void SetViewToWindow();

        void Tick(double time_delta) override {
            controller_->Tick(time_delta);
            DynamicObject::Tick(time_delta);
            UpdateView();
        }
    };

    using CameraPtr = std::shared_ptr<Camera>;
}