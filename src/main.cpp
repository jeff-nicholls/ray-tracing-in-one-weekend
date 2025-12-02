#include <cassert>
#include <cstddef>
#include <iostream>

#include "colour.hpp"
#include "ray.hpp"
#include "vec3.hpp"

namespace {

Colour ray_colour(Ray const& ray) {
    Vec3 const unit_direction = unit_vector(ray.get_direction());
    double const y_parametric = 0.5 * (unit_direction.y() + 1.0);
    return ((1.0 - y_parametric) * Colour{1.0, 1.0, 1.0}) + (y_parametric * Colour{0.5, 0.7, 1.0});
}

}  // namespace

int main() {
    // Image parameters.
    double const aspect_ratio = 16.0 / 9.0;
    unsigned int const image_width = 400;

    // Calculate image height, and ensure it's not zero.
    auto const image_height = static_cast<unsigned int>(image_width / aspect_ratio);
    assert(image_height > 0);

    // Camera
    double const focal_length = 1.0;
    double const viewport_height = 2.0;
    double const viewport_width =
        viewport_height * (static_cast<double>(image_width) / static_cast<double>(image_height));
    Point3 const camera_center{0, 0, 0};

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vec3 const viewport_u{viewport_width, 0, 0};
    Vec3 const viewport_v{0, -viewport_height, 0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    Vec3 const pixel_delta_u = viewport_u / image_width;
    Vec3 const pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    Point3 const viewport_upper_left =
        camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    Point3 const pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (size_t j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (size_t i = 0; i < image_width; i++) {
            Point3 const pixel_center = pixel00_loc + (static_cast<double>(i) * pixel_delta_u) +
                                        (static_cast<double>(j) * pixel_delta_v);
            Vec3 const ray_direction = pixel_center - camera_center;
            Ray const ray(camera_center, ray_direction);

            Colour const pixel_colour = ray_colour(ray);
            write_colour(std::cout, pixel_colour);
        }
    }
    std::clog << "\rDone.                   \n";
}
