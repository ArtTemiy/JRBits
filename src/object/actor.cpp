//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/object/actor.hpp>

namespace Engine {
    void Actor::Tick(double time_delta) {
        controller_->Tick(time_delta);
        DynamicObject::Tick(time_delta);
    }

    void Actor::Draw(const Coordinates &coordinates, Drawable::Camera &camera) {
        drawable_->Draw(coordinates, camera);
    }

    bool ActorTextureLoader::LoadData() {
        return false;
    }
}