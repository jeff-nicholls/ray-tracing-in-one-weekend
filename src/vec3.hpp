#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>

class Vec3 {
   public:
    static constexpr size_t DIMENSIONS = 3;

    Vec3() : elements{0, 0, 0} {}

    Vec3(double element0, double element1, double element2)
        : elements{element0, element1, element2} {}

    [[nodiscard]] double x() const { return elements[0]; }
    [[nodiscard]] double y() const { return elements[1]; }
    [[nodiscard]] double z() const { return elements[2]; }

    [[nodiscard]] double length() const { return std::sqrt(length_squared()); }

    [[nodiscard]] double length_squared() const {
        return (this->elements[0] * this->elements[0]) + (this->elements[1] * this->elements[1]) +
               (this->elements[2] * this->elements[2]);
    }

    Vec3 operator-() const { return {-this->elements[0], -this->elements[1], -this->elements[2]}; }

    double& operator[](size_t idx) {
        assert(idx < DIMENSIONS);
        return elements.at(idx);
    }

    double const& operator[](size_t idx) const {
        assert(idx < DIMENSIONS);
        return elements.at(idx);
    }
    Vec3& operator+=(Vec3 const& vec) {
        elements[0] += vec.elements[0];
        elements[1] += vec.elements[1];
        elements[2] += vec.elements[2];
        return *this;
    }

    Vec3& operator*=(double scalar) {
        elements[0] *= scalar;
        elements[1] *= scalar;
        elements[2] *= scalar;
        return *this;
    }

    Vec3& operator/=(double scalar) {
        assert(scalar != 0);
        return *this *= (1 / scalar);
    }

    friend Vec3 operator+(Vec3 const& vec_a, Vec3 const& vec_b);
    friend Vec3 operator-(Vec3 const& vec_a, Vec3 const& vec_b);
    friend Vec3 operator*(Vec3 const& vec_a, Vec3 const& vec_b);
    friend Vec3 operator*(double scalar, Vec3 const& vec_b);
    friend Vec3 operator*(Vec3 const& vec_a, double scalar);
    friend double dot(Vec3 const& vec_a, Vec3 const& vec_b);
    friend Vec3 cross(Vec3 const& vec_a, Vec3 const& vec_b);

   private:
    std::array<double, DIMENSIONS> elements;
};

using Point3 = Vec3;

inline std::ostream& operator<<(std::ostream& out, Vec3 const& vec) {
    return out << vec.x() << ' ' << vec.y() << ' ' << vec.z();
}

inline Vec3 operator+(Vec3 const& vec_a, Vec3 const& vec_b) {
    return {vec_a.elements[0] + vec_b.elements[0], vec_a.elements[1] + vec_b.elements[1],
            vec_a.elements[2] + vec_b.elements[2]};
}

inline Vec3 operator-(Vec3 const& vec_a, Vec3 const& vec_b) {
    return {vec_a.elements[0] - vec_b.elements[0], vec_a.elements[1] - vec_b.elements[1],
            vec_a.elements[2] - vec_b.elements[2]};
}

inline Vec3 operator*(Vec3 const& vec_a, Vec3 const& vec_b) {
    return {vec_a.elements[0] * vec_b.elements[0], vec_a.elements[1] * vec_b.elements[1],
            vec_a.elements[2] * vec_b.elements[2]};
}

inline Vec3 operator*(double scalar, Vec3 const& vec) {
    return {scalar * vec.elements[0], scalar * vec.elements[1], scalar * vec.elements[2]};
}

inline Vec3 operator*(Vec3 const& vec, double scalar) {
    return scalar * vec;
}

inline Vec3 operator/(Vec3 const& vec, double scalar) {
    return (1 / scalar) * vec;
}

inline double dot(Vec3 const& vec_a, Vec3 const& vec_b) {
    return (vec_a.elements[0] * vec_b.elements[0]) + (vec_a.elements[1] * vec_b.elements[1]) +
           (vec_a.elements[2] * vec_b.elements[2]);
}

inline Vec3 cross(Vec3 const& vec_a, Vec3 const& vec_b) {
    return {(vec_a.elements[1] * vec_b.elements[2]) - (vec_a.elements[2] * vec_b.elements[1]),
            (vec_a.elements[2] * vec_b.elements[0]) - (vec_a.elements[0] * vec_b.elements[2]),
            (vec_a.elements[0] * vec_b.elements[1]) - (vec_a.elements[1] * vec_b.elements[0])};
}

inline Vec3 unit_vector(Vec3 const& vec) {
    return vec / vec.length();
}
