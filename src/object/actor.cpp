//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/object/actor.hpp>

namespace Engine {
    void IActor::Draw(const Coordinates &coordinates, Drawable::Camera &camera) {
        drawable_->Draw(coordinates, camera);
    }

    bool ActorTextureLoader::LoadData() {
        return false;
    }
}