//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/object/actor.hpp>

namespace Engine {
    void IActor::Draw(Drawable::ICamera &camera) {
        if (!drawable_) {
            throw std::runtime_error("No drawable component");
        }
        drawable_->SetPosition(GetCoordinates());
        drawable_->Draw(camera);
    }

    bool ActorTextureLoader::LoadData() {
        return false;
    }
}