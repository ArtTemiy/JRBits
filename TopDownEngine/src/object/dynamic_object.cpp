//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/object/dynamic_object.hpp>
#include <TopDownEngine/utils/display_logger.hpp>

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
        }
    }

    template<>
    void DynamicObject::ProcessCollision<DynamicObject>(const Object& intersection_object, const DynamicObject& other) {
//        velocity_ = 0;
        moving_direction_ = {0, 0};
    }

    template<class OtherObject>
    void DynamicObject::ProcessCollision(const Object &intersection_object, const OtherObject &other) {
    }

    /// Intersection between DYNAMIC and STATIC
    /// @param [in] dynamic_object must be dynamic
    /// @param [out] static_object must be static
    void ProcessCollision(DynamicObject& dynamic_object, DynamicObject& static_object) {
        assert(dynamic_object.GetCollisionType() == DynamicObject::kDynamic);
        assert(static_object.GetCollisionType() == DynamicObject::kStatic);

        auto intersection = dynamic_object.Intersection(static_object);
        if (!intersection) {
            return;
        }
        auto& intersection_object = intersection.value();

        auto new_coordinates = dynamic_object.GetCoordinates();
        int axis = intersection_object.GetSize()[0] < intersection_object.GetSize()[1] ? 0 : 1;
        if (intersection_object.GetCoordinates()[axis] <= static_object.GetCoordinates()[axis]) {
            new_coordinates[axis] -= intersection_object.GetSize()[axis];
        } else {
            new_coordinates[axis] += intersection_object.GetSize()[axis];
        }
        dynamic_object.SetCoordinates(new_coordinates);

        dynamic_object.ProcessCollision(intersection_object, static_object);
        static_object.ProcessCollision(intersection_object, dynamic_object);
    }
}
