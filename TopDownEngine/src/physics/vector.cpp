//
// Created by Artemiy Shvedov on 02.04.21.
//

#include <TopDownEngine/core/physics/vector.hpp>

#include <glog/logging.h>

#include <cmath>

namespace Engine {

    double Norm(const Vector &v) {
        return std::sqrt(std::pow(v[0], 2) + std::pow(v[1], 2));
    }

    Vector operator-(const Vector& v) {
        return {-v[0], -v[1]};
    }

    Vector& operator+=(Vector& v1, const Vector& v2) {
        v1[0] += v2[0];
        v1[1] += v2[1];
        return v1;
    }

    Vector& operator-=(Vector& v1, const Vector& v2) {
        return (v1 += (-v2));
    }

    Vector operator+(const Vector& v1, const Vector& v2) {
        auto result = v1;
        result += v2;
        return result;
    }

    Vector operator-(const Vector& v1, const Vector& v2) {
        return v1 + (-v2);
    }

    Vector Engine::operator*=(Vector &v1, const Vector &v2) {
        v1[0] *= v2[0];
        v1[1] *= v2[1];
        return v1;
    }

    Vector Engine::operator*(const Vector &v1, const Vector &v2) {
        auto result = v1;
        result *= v2;
        return result;
    }

    Vector Engine::operator/=(Vector &v1, const Vector &v2) {
        if (Norm(v2) == 0) {
            LOG(WARNING) << "Vector norm is 0 in vector division";
            return v1;
        }
        v1[0] *= v2[0] == 0 ? 1 : v2[0];
        v1[1] *= v2[1] == 0 ? 1 : v2[1];
        return v1;
    }

    Vector Engine::operator/(const Vector &v1, const Vector &v2) {
        auto result = v1;
        result /= v2;
        return result;
    }

    Vector& operator*=(Vector& v1, double c) {
        v1[0] *= c;
        v1[1] *= c;
        return v1;
    }

    Vector& operator/=(Vector& v1, double c) {
        return v1 *= (1 / c);
    }

    Vector operator*(const Vector& v1, double c) {
        auto result = v1;
        result *= c;
        return result;
    }

    Vector operator/(const Vector& v1, double c) {
        return v1 * (1 / c);
    }

    sf::Vector2f ToSFVector2f(const Vector& v) {
        return sf::Vector2f(
            static_cast<float>(v[1]),
            static_cast<float>(v[0]));
    }

    std::ostream& operator<<(std::ostream& out, const Vector& vector) {
        out << "[" << vector[0] << ", " << vector[1] << "]";
        return out;
    }
}
