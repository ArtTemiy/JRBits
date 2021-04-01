//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/Core.h>

using MovingDirection = std::array<double, 2>;

namespace Engine {
/// Dynamic object with moving ability
    class DynamicObject : public Object, Tickable {
        /// Maximum possible velocity
        double max_velocity_;
        ///Moving direction (with norm = 1)
        MovingDirection moving_direction_ = {0, 0};

    public:
        DynamicObject(Object object, double max_velocity)
                : Object(object),
                  max_velocity_(max_velocity) {}

        MovingDirection GetMovingDirection() const;

        void SetMovingDirection(const MovingDirection &new_moving_direction);

        void Tick(double time_delta) override;
    };

    using DynamicObjectPtr = std::shared_ptr<DynamicObject>;
}