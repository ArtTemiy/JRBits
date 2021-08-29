//
// Created by Artemiy Shvedov on 01.08.21.
//

#pragma once

#include "actor.hpp"

namespace Engine {
    class InvisibleActor : public Actor {
    public:
        explicit InvisibleActor(DynamicObject object, World* world = nullptr) : Actor(std::move(object), world) {}

        void Draw(Drawable::Camera &camera) override {}
    };
} // namespace Engine