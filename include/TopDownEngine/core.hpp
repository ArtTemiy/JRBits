//
// Created by ArtTemiy on 28.02.2021.
//

#pragma once

#include <array>

namespace Engine {
    /// Class with tick function that called every frame
    class Tickable {
    public:
        /// called every frame
        /// @param [in] time_delta Time passed form precious frame
        virtual void Tick(double time_delta) = 0;
    };

    using Coordinates = std::array<double, 2>;
    using Size = std::array<double, 2>;

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
