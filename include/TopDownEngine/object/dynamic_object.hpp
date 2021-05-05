//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/physics/vector.hpp>

#include <optional>

using MovingDirection = std::array<double, 2>;

namespace Engine {
    /// Dynamic object with moving ability
    class DynamicObject : public Object, Tickable {
    public:

        enum CollisionType {
            kDynamic,
            kStatic,
            kNoCollision
        };

    private:
        /// Maximum possible velocity
        double velocity_;

        ///Moving direction (with norm = 1)
        MovingDirection moving_direction_ = {0, 0};

        const CollisionType collision_type_;

    public:
        DynamicObject(Object object, double max_velocity, const CollisionType collision_type = kNoCollision)
                : Object(object),
                  velocity_(max_velocity),
                  collision_type_(collision_type) {
        }

        DynamicObject(const Coordinates &coordinates, const Size &size, double velocity, const CollisionType collision_type = kNoCollision)
        : Object(coordinates, size),
          velocity_(velocity),
          collision_type_(collision_type) {
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

        auto& GetCollisionDynamic() const {
            return collision_type_;
        }

        /// Processes collision with another object (can change only itself)
        template<class OtherObject>
        void ProcessCollision(const Object& intersection_object, const OtherObject& other);

    private:
        /// Changes moving_direction, so it has norm equal to 1
        void NormalizeMovingDirection();
    };

    /// Processes collision between two objects
    void ProcessCollision(DynamicObject& dynamic_object, DynamicObject& static_object);

    using DynamicObjectPtr = std::shared_ptr<DynamicObject>;
}