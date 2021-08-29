//
// Created by Artemiy Shvedov on 06.05.21.
//

#pragma once

#include <TopDownEngine/core/physics/vector.hpp>

#include <optional>

namespace Engine {
    using Coordinates = Vector;
    using Size = Vector;

    /// Simple box object: coordinates (of left upper corner) and size
    class Object {
        Coordinates coordinates_;
        Size size_;

    public:
        /// @param [in] coordinates - Coordinates of the object
        /// @param [in] size - Size of the object
        Object(Coordinates coordinates = {0, 0}, Size size = {0, 0})
                : coordinates_(coordinates),
                  size_(size) {}

        virtual ~Object() = default;

        Coordinates GetCoordinates() const;

        void SetCoordinates(const Coordinates& new_coordinates);

        Size GetSize() const;

        /// Returns if the point is inside the object rectangle
        /// @param [in] coordinates - coordinates of the point
        /// @returns if the point inside object rectangle
        bool PointInside(const Coordinates& coordinates);

        /// If object intersects with another
        /// @param [in] object - another object
        /// @return if object intersects
        bool Intersects(const Object& object) const;

        /// Returns intersection as object
        /// @param [in] object - another object
        /// @return std::nullopt if objects don't intersects,
        /// otherwise object that describes intersection
        std::optional<Object> Intersection(const Object& object) const;

        double Distance(const Object& object) const;
    };

    inline bool Intersects(const Object& object1, const Object& object2) {
        return object1.Intersects(object2);
    }

    inline std::optional<Object> Intersection(const Object& object1, const Object& object2) {
        return object1.Intersection(object2);
    }

    inline double Distance(const Object& object1, const Object& object2) {
        return object1.Distance(object2);
    }

    std::ostream& operator<<(std::ostream& out, const Object& obj);
}
