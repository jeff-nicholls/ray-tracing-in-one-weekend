#pragma once

#include "vec3.hpp"

class Ray {
   public:
    Ray() = default;

    Ray(Point3 const& origin_in,  // NOLINT(bugprone-easily-swappable-parameters)
        Vec3 const& direction_in)
        : origin(origin_in), direction(direction_in) {}

    [[nodiscard]] Point3 const& get_origin() const { return origin; }
    [[nodiscard]] Vec3 const& get_direction() const { return direction; }

    [[nodiscard]] Point3 at(double scalar) const { return origin + (scalar * direction); }

   private:
    Point3 origin;
    Vec3 direction;
};
