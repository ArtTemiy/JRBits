//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/object/dynamic_object.hpp>
#include <cmath>

namespace Engine {
    MovingDirection DynamicObject::GetMovingDirection() const {
        return moving_direction_;
    }

    void DynamicObject::SetMovingDirection(const MovingDirection &new_moving_direction) {
        auto new_moving_direction_norm = std::sqrt(
                new_moving_direction[0] * new_moving_direction[0] +
                new_moving_direction[1] * new_moving_direction[1]
        );
        moving_direction_ = {
                new_moving_direction[0] / new_moving_direction_norm,
                new_moving_direction[1] / new_moving_direction_norm
        };
    }

    void DynamicObject::Tick(double time_delta) {
        const auto &coordinates = Object::GetCoordinates();
        Object::SetCoordinates({
                coordinates[0] + max_velocity_ * time_delta * moving_direction_[0],
                coordinates[1] + max_velocity_ * time_delta * moving_direction_[1],
        });
    }
}