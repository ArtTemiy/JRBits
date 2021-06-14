//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <SFML/System/Vector2.hpp>

#include <array>
#include <iostream>

namespace Engine {
    using Vector = std::array<double, 2>;

    double Norm(const Vector& v);

    Vector operator-(const Vector& v);

    Vector& operator+=(Vector& v1, const Vector& v2);

    Vector& operator-=(Vector& v1, const Vector& v2);

    Vector operator+(const Vector& v1, const Vector& v2);

    Vector operator-(const Vector& v1, const Vector& v2);

    Vector operator*=(Vector& v1, const Vector& v2);

    Vector operator*(const Vector& v1, const Vector& v2);

    Vector operator/=(Vector& v1, const Vector& v2);

    Vector operator/(const Vector& v1, const Vector& v2);

    Vector& operator*=(Vector& v1, double c);

    Vector& operator/=(Vector& v1, double c);

    Vector operator*(const Vector& v1, double c);

    Vector operator/(const Vector& v1, double c);

    std::ostream& operator<<(std::ostream& out, const Vector& vector);

    sf::Vector2f ToSFVector2f(const Vector& v);

    template<class T>
    Vector ToVector(const T& vector) {
        return {
                static_cast<double>(vector[0]),
                static_cast<double>(vector[1])
        };
    }

    template<class T>
    Vector ToVector(const sf::Vector2<T>& vector) {
        return {
                static_cast<double>(vector.y),
                static_cast<double>(vector.x)
        };
    }
}
