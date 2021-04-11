//
// Created by ArtTemiy on 28.02.2021.
//

#pragma once

#include <TopDownEngine/physics/vector.hpp>

#include <array>

namespace Engine {
    using uint = uint32_t;

    /// Class with tick function that called every frame
    class Tickable {
    public:
        /// called every frame
        /// @param [in] time_delta Time passed form precious frame
        virtual void Tick(double time_delta) = 0;
    };

    using Coordinates = Vector;
    using Size = Vector;

    /// Simple box object
    class Object {
        Coordinates coordinates_;
        Size size_;

    public:
        Object(Coordinates coordinates, Size size)
                : coordinates_(coordinates),
                  size_(size) {}

        Coordinates GetCoordinates() const;

        void SetCoordinates(const Coordinates& new_coordinates);

        Size GetSize() const;
    };
}
