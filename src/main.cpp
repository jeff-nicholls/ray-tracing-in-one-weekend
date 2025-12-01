#include <iostream>

#include "colour.hpp"

int main() {
    // Image parameters.
    constexpr size_t IMAGE_WIDTH = 256;
    constexpr size_t IMAGE_HEIGHT = 256;

    // Render
    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";
    for (size_t j = 0; j < IMAGE_HEIGHT; j++) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - j) << ' ' << std::flush;
        for (size_t i = 0; i < IMAGE_WIDTH; i++) {
            auto pixel_color =
                Colour(double(i) / (IMAGE_WIDTH - 1), double(j) / (IMAGE_HEIGHT - 1), 0);
            write_colour(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                   \n";
}
