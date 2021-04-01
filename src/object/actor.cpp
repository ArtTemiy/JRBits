//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/object/actor.hpp>

namespace Engine {
    void Actor::Tick(double time_delta) {
        controller_->Tick(time_delta);
        DynamicObject::Tick(time_delta);
    }
}