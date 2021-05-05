//
// Created by ArtTemiy on 28.02.2021.
//

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/physics/vector.hpp>

namespace Engine {
    Coordinates Object::GetCoordinates() const {
        return coordinates_;
    }

    void Object::SetCoordinates(const Coordinates &new_coordinates) {
        coordinates_ = new_coordinates;
    }

    Size Object::GetSize() const {
        return size_;
    }

    bool Object::Intersects(const Object &object) {
        return std::min(coordinates_[0] + size_[0], object.coordinates_[0] + object.size_[0]) - std::max(coordinates_[0], object.coordinates_[0]) > 0 &&
               std::min(coordinates_[1] + size_[1], object.coordinates_[1] + object.size_[1]) - std::max(coordinates_[1], object.coordinates_[1]) > 0;
    }

    std::optional<Object> Object::Intersection(const Object &object) {
        if (!Intersects(object)) {
            return std::nullopt;
        }
        return Object(
                {std::max(coordinates_[0], object.coordinates_[0]),
                 std::max(coordinates_[1], object.coordinates_[1])},
                {std::min(coordinates_[0] + size_[0], object.coordinates_[0] + object.size_[0]) - std::max(coordinates_[0], object.coordinates_[0]),
                 std::min(coordinates_[1] + size_[1], object.coordinates_[1] + object.size_[1]) - std::max(coordinates_[1], object.coordinates_[1])}
        );
    }

    std::ostream& operator<<(std::ostream& out, const Object& obj) {
        out << "{ c: " << obj.GetCoordinates() << ", s: " << obj.GetSize() << " }";
        return out;
    }
}