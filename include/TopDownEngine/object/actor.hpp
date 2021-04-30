//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/core/loader.hpp>
#include <TopDownEngine/controller/controller.hpp>
#include <TopDownEngine/controller/player_controller.hpp>
#include <TopDownEngine/drawable/drawable.hpp>

#include "dynamic_object.hpp"

namespace Engine {

    /// Actor interface
    class IActor : public DynamicObject, Drawable::IDrawable {
        Drawable::IDrawablePtr drawable_;
    public:
        explicit IActor(DynamicObject object) : DynamicObject(std::move(object)) {}

        Drawable::IDrawablePtr &GetDrawable() {
            return drawable_;
        }

        void SetDrawable(const Drawable::IDrawablePtr &drawable) {
            drawable_ = drawable;
        }

        void SetSize(uint height, uint width) override {
            drawable_->SetSize(height, width);
        }

        virtual Controller::IController& GetController() = 0;

        void Draw(const Coordinates &coordinates, Drawable::Camera &camera) override;
    };

    /// Actor - dynamic object with controller, given via template
    template <class ControllerT>
    class Actor : public IActor {
        using ControllerPtr = std::shared_ptr<ControllerT>;
        ControllerT controller_;

    public:
        explicit Actor(DynamicObject object)
                : IActor(std::move(object)),
                  controller_(*this) {
        }

        Controller::IController& GetController() override {
            return controller_;
        }

        void Tick(double time_delta) override;
    };

    template<class ControllerT>
    void Actor<ControllerT>::Tick(double time_delta) {
        controller_.Tick(time_delta);
        DynamicObject::Tick(time_delta);
    }

    class ActorTextureLoader : Loader<std::shared_ptr<sf::Texture>> {
        bool LoadData() override;
    };
}