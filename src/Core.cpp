//
// Created by ArtTemiy on 28.02.2021.
//

#include <TopDownEngine/Core.h>

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
}