#pragma once

#include <iostream>

#include "vec3.hpp"

using Colour = Vec3;

void inline write_colour(std::ostream& out, Colour const& pixel_color) {
    auto red = pixel_color.x();
    auto green = pixel_color.y();
    auto blue = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int const rbyte = static_cast<int>(255.999 * red);
    int const gbyte = static_cast<int>(255.999 * green);
    int const bbyte = static_cast<int>(255.999 * blue);

    // Write out the pixel Colour components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
