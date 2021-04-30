//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/core/loader.hpp>
#include <TopDownEngine/controller/controller.hpp>
#include <TopDownEngine/drawable/drawable.hpp>

#include "dynamic_object.hpp"

namespace Engine {

    /// Actor - dynamic object with controller
    // TODO - make controller template type
    class Actor : public DynamicObject, Drawable::IDrawable {
        Controller::ControllerPtr controller_;
        Drawable::IDrawablePtr drawable_;

    public:
        Actor(DynamicObject object, Controller::ControllerPtr controller)
                : DynamicObject(std::move(object)),
                  controller_(std::move(controller)) {
            controller_->Init(this);
        }

        Drawable::IDrawablePtr &GetDrawable() {
            return drawable_;
        }

        void SetDrawable(const Drawable::IDrawablePtr &drawable) {
            drawable_ = drawable;
        }

        void SetSize(uint height, uint width) override {
            drawable_->SetSize(height, width);
        }

        auto& GetController() {
            return controller_;
        }

        void Draw(const Coordinates &coordinates, Drawable::Camera &camera) override;

        void Tick(double time_delta) override;
    };

    class ActorTextureLoader : Loader<std::shared_ptr<sf::Texture>> {
        bool LoadData() override;
    };
}