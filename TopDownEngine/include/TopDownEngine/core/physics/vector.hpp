//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <SFML/System/Vector2.hpp>

#include <array>
#include <iostream>

namespace Engine {
    /// Vector: (y, x)
    struct Vector {
        double y, x;

        Vector(double y, double x) : y(y), x(x) {}
        Vector(std::array<double, 2> arr) : y(arr[0]), x(arr[1]) {}
        Vector(std::initializer_list<double> list) {
            assert(list.size() == 2);
            y = *list.begin();
            x = *(list.begin() + 1);
        }

        double operator[](size_t axis) const {
            assert(axis < 2);
            if (axis) {
                return x;
            } else {
                return y;
            }
        }
        double& operator[](size_t axis) {
            assert(axis < 2);
            if (axis) {
                return x;
            } else {
                return y;
            }
        }

        bool operator==(const Vector& rhs) const {
            return std::tie(y, x) == std::tie(rhs.y, rhs.x);
        }

        bool operator!=(const Vector& rhs) const {
            return !(rhs == *this);
        }
    };
//    using Vector = std::array<double, 2>;

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
