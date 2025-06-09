#include <iostream>

int main(int argc, char** argv) {
    // Image
    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";


    // rendering the image
    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << '\n' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
            // Output:
            // 220 220 0
            // 221 220 0
            // 222 220 0
            // ...

            // This prints out a pixel with rgb values. 
            // So the first pixel has red=220, green=220, and blue=0
            // By convention, each of the red/green/blue components are represented internally by real-valued variables that range from 0.0 to 1.0.
            // These must be scaled to integer values between 0 and 255 before we print them out


        }
    }
    std::clog << "\rDone.                 \n";
}