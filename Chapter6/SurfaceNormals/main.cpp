#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <fstream>
#include <iostream>

// this checks if there are any rays that intersect with the sphere
// returns true if discriminant >= 0 (1 or more solutions)
double hit_sphere(const vec::point3& center, double radius, const ray& r) {
    vec::vec3 oc = center - r.origin(); // oc = C - Q
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc); // = -2 (d·(C−Q))
    auto c = dot(oc, oc) - radius * radius; // = (C−Q)·(C−Q) - r^2
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}

// ray_color takes the second parameter (the direction of the ray), and normalizes it.
color ray_color(const ray& r, bool debug = false, std::ofstream* debug_file=nullptr) {
    auto t = hit_sphere(vec::point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec::vec3 N = vec::unit_vector(r.at(t) - vec::vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    
    // if the ray doesn't intersect the sphere, then return the sky color
    // sky color is derived through linear interpolation
    vec::vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);    
    color result = (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);

    if (debug && debug_file!=nullptr) {
        *debug_file << "unit_direction = " << unit_direction << "\n";
        *debug_file << "a = " << a << "\n";
        *debug_file << "(1.0 - a) = " << (1.0 - a) << "\n";
        *debug_file << "A = (1.0 - a) * color(1.0, 1.0, 1.0) = " << (1.0 - a) * color(1.0, 1.0, 1.0) << "\n";
        *debug_file << "B = a * color(0.5, 0.7, 1.0) = " << a * color(0.5, 0.7, 1.0) << "\n";
        *debug_file << "A+B = ((1.0 - a) * color(1.0, 1.0, 1.0)) + (a * color(0.5, 0.7, 1.0)) = " << result << "\n";
        *debug_file << "result = " << result << "\n";
    }
    return result;
}




int main(int argc, char** argv) {
    // To debug and read the values of viewport_width, image_height, and other derived values
    std::ofstream debug_file("debug.txt");


    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    
    // DEBUG: image_height
    debug_file << "image_height = " << image_height << "\n";

    // Camera
    // focal_length = distance between the viewport and the camera center point
    auto focal_length = 1.0;
    // arbitrary viewport height of 2.0
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
   
    // DEBUG: viewport_width
    debug_file << "viewport_width = " << viewport_width << "\n";
    debug_file << "viewport_height = " << viewport_height << "\n";

    // we'll start with the camera centered at (0,0,0) -> (x,y,z)
    auto camera_center = vec::point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec::vec3(viewport_width, 0, 0);
    auto viewport_v = vec::vec3(0, -viewport_height, 0);

    // DEBUG: viewport_u, viewport_v
    debug_file << "viewport_u = " << viewport_u << "\n";
    debug_file << "viewport_v = " << viewport_v << "\n";

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // DEBUG: pixel_delta_u, pixel_delta_v
    debug_file << "pixel_delta_u = " << pixel_delta_u << "\n";
    debug_file << "pixel_delta_v = " << pixel_delta_v << "\n";
    // pixel_delta_u = 3.55556 * (1/400)
    // pixel_delta_v = (-2) * (1/225)
    // pixel_delta_v = (1/image_height) * (-viewport_height)

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
        - vec::vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    
    // DEBUG: viewport_upper_left
    debug_file << "viewport_upper_left = " << viewport_upper_left << "\n";    
    
    // DEBUG: viewport_upper_left steps
    debug_file << "viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u / 2 - viewport_v / 2\n";
    debug_file << "Values: "
        << "(" << camera_center << ") - "
        << "(" << vec::vec3(0, 0, focal_length) << ") - ("
        << viewport_u <<")/2 - (" << viewport_v << ")/2"
        << "\n";

    
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    debug_file << "pixel00_loc (0,0) = (" << pixel00_loc << ")\n";
    // this location is (0,0), the top left pixel

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    
    // DEBUG: pixel_center when i,j = 1
    auto pixel_centerTest = pixel00_loc + (0 * pixel_delta_u) + (0 * pixel_delta_v);
    debug_file << "pixel_center (0,0) = (" << pixel_centerTest << ")\n";

    // DEBUG: ray_color when i,j = 1
    auto test_ray_direction = pixel_centerTest - camera_center;
    ray test_ray(camera_center, test_ray_direction);

    color test_color = ray_color(test_ray, true, &debug_file);
    debug_file << "ray_color for pixel (0,0) = ("
        << test_color << ")\n";
    debug_file << "PPM-style output: ";
    write_color(debug_file, test_color);


    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            
            // ray_direction isn't normalized
            auto ray_direction = pixel_center - camera_center;
            
            // ray(origin, direction)
            ray r(camera_center, ray_direction);
            
            // ray_color normalizes ray_direction by calling unit_vector
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}