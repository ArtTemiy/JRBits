//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/physics/vector.hpp>

using MovingDirection = std::array<double, 2>;

namespace Engine {
    /// Dynamic object with moving ability
    class DynamicObject : public Object, Tickable {
        /// Maximum possible velocity
        double velocity_;
        ///Moving direction (with norm = 1)
        MovingDirection moving_direction_ = {0, 0};

    public:
        DynamicObject(Object object, double max_velocity)
                : Object(object),
                  velocity_(max_velocity) {
        }

        DynamicObject(const Coordinates &coordinates, const Size &size, double velocity)
        : Object(coordinates, size),
          velocity_(velocity) {
        }

        MovingDirection GetMovingDirection() const;

        void SetMovingDirection(const MovingDirection& new_moving_direction);

        void AddMovingDirection(const MovingDirection& new_moving_direction);

        void Tick(double time_delta) override;

        double GetVelocity() const {
            return velocity_;
        }

        void SetVelocity(double velocity) {
            velocity_ = velocity;
        }

    private:
        /// Changes moving_direction, so it has norm equal to 1
        void NormalizeMovingDirection();
    };

    using DynamicObjectPtr = std::shared_ptr<DynamicObject>;
}