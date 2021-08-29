//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/object/actor.hpp>
#include <TopDownEngine/world/world.hpp>
#include <TopDownEngine/controller/null_controller.hpp>

namespace Engine {
    void Actor::SetCollisionType(DynamicObject::CollisionType collision_type) {
        DynamicObject::SetCollisionType(collision_type);
        if (world_) {
            world_->OnActorEdit(shared_from_this());
        }
    }

    void Actor::Tick(double time_delta) {
        controller_->Tick(time_delta);
        DynamicObject::Tick(time_delta);
        WithDrawableComponent::Tick(time_delta);
    }

    void Actor::CheckCorrectness() {
        if (!controller_) {
            SetController(std::make_shared<Engine::Controller::NullController>());
            LOG(WARNING) << "No controller was set, so null controller is created";
        }
    }
} // Engine