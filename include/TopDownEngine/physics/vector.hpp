//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <array>
#include <SFML/System/Vector2.hpp>

using Vector = std::array<double, 2>;

Vector operator-(const Vector& v);

Vector& operator+=(Vector& v1, const Vector& v2);

Vector& operator-=(Vector& v1, const Vector& v2);

Vector operator+(const Vector& v1, const Vector& v2);

Vector operator-(const Vector& v1, const Vector& v2);

Vector& operator*=(Vector& v1, double c);

Vector& operator/=(Vector& v1, double c);

Vector operator*(const Vector& v1, double c);

Vector operator/(const Vector& v1, double c);

sf::Vector2f ToSFVector2f(const Vector& v);