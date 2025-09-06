#include "color.h"
#include "vec3.h"

#include <iostream>

int main(int argc, char** argv) {
    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            // pixel_color stores normalized RGB values in [0, 1]
            auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
            // write_color scales these to [0, 255] for the PPM file
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}
