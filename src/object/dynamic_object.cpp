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
        moving_direction_ = new_moving_direction;
    }

    void DynamicObject::Tick(double time_delta) {
        const auto &coordinates = Object::GetCoordinates();
        NormalizeMovingDirection();
        Object::SetCoordinates({
                coordinates[0] + velocity_ * time_delta * moving_direction_[0],
                coordinates[1] + velocity_ * time_delta * moving_direction_[1],
        });
    }

    void DynamicObject::AddMovingDirection(const MovingDirection &new_moving_direction) {
        moving_direction_ = moving_direction_ + new_moving_direction;
    }

    void DynamicObject::NormalizeMovingDirection() {
        auto moving_direction_norm = std::sqrt(
                std::pow(moving_direction_[0], 2) +
                std::pow(moving_direction_[1], 2)
        );
        if (moving_direction_norm != 0) {
            moving_direction_ = {
                    moving_direction_[0] / moving_direction_norm,
                    moving_direction_[1] / moving_direction_norm
            };
        };
    }
}