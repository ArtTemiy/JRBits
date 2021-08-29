//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/core/loaders/loader.hpp>
#include <TopDownEngine/controller/controller.hpp>
#include <TopDownEngine/controller/player_controller.hpp>
#include <TopDownEngine/drawable/drawable.hpp>
#include <TopDownEngine/world/world_fwd.hpp>

#include "dynamic_object.hpp"

namespace Engine {

    /// Actor interface
    // TODO - think about controller and templates
    class Actor : public DynamicObject, public Drawable::WithDrawableComponent, std::enable_shared_from_this<Actor> {
        World* world_ = nullptr;
        bool destroy_ = false;
        Controller::ControllerPtr controller_;

    public:
        explicit Actor(DynamicObject object, World* world = nullptr)
        : DynamicObject(std::move(object)),
          WithDrawableComponent(*static_cast<Object*>(this)),
          world_(world) {}

        void Tick(double time_delta) override;

        World* GetWorld() const { return world_; }
        void SetWorld(World* world) { world_ = world; }

        bool IsDestroy() const { return destroy_; }
        void SetDestroy(bool destroy) { destroy_ = destroy; }

        void SetCollisionType(CollisionType collision_type) override;

        Controller::ControllerPtr GetController() {
            return controller_;
        }

        void SetController(const Controller::ControllerPtr& controller) {
            controller_ = controller;
            controller_->SetControllable(this);
        }

        void CheckCorrectness();
    };
}