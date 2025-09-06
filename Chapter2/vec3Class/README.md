# Chapter #3: The vec3 Class

- We’ll use the same class vec3 for colors, locations, directions, offsets
- Some people don’t like this because it doesn’t prevent you from doing something silly, like subtracting a position from a color. 
- we do declare two aliases for vec3: point3 and color to differentiate


### Commands to compile as Image file:
- Because the file is written to the standard output stream, you'll need to redirect it to an image file
- get the debug build from CMake running this command:
    ```
    cmake -B build
    cmake --build build
    ```
- Then navigate to build\Debug\nameInCMakeLists.exe:
- Then run:
- ```build\Debug\inOneWeekend.exe > image.ppm```


### CMakeLists.txt
This file is made up of 3 functions (so far):
1. `cmake_minimum_required(VERSION 3.10)`
    - specifies a minimum CMake version
    - establishes policy settings and ensures that the following CMake functions are run with a compatible version of CMake

2. `project(vec3)`
    - sets the project name
    - required with every project and should be called soon after cmake_minimum_required()

3. `add_executable(vec3 vec3.cpp main.cpp)`
    - the `add_executable(name, options,... sources...)` command tells CMake to create a .exe file using the specified source code files.
    - add_executable should include ALL source code (name, i.e. all .cpp files)
    - the name argument is the name of the .exe file
        - >build\Debug\nameInCMakeLists.exe



#### First we do:
`auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);`
- `color` is a type alias for `vec::vec3`, 
    - `using color = vec::vec3;` is in color.h

This results in `e[0]`, `e[1]`, and `e[2]` (attributes of an instance of vec3) being set to a number between `0` and `1`.

However, we then go to call `void write_color(std::ostream& out, const color& pixel_color)`

`write_color`, normalizes the `i`, or `j` values. 

For example in the 2nd iteration of the inner loop:

``` cpp
for (int j = 0; j < image_height; j++) {        
    for (int i = 0; i < image_width; i++) {
        auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);    
        write_color(std::cout, pixel_color);
    }
}
```

If, `i=1` and `j=0`, we divide `i` by 255, resulting in `0.0039215686`. 
**In graphics, color components are often stored as normalized values between 0.0 and 1.0.**


`0.0039215686` is a perfectly fine number for a color, however, we need to normalize it so that it fits the `.ppm` file's PPM-compatible 8-bit color value. 

PPM files require an 8 bit color value [0-255]. Therefore we multiply it by 255.999.

#### Question: What if `i=255`?
If `i=255`, since the loop goes until i < 256, meaning at the end we get `i=255`. And i/255 = 1. 

This means that 1*255.999=255.999 wouldnt that go over 255?

#### Answer:

No it wouldn't go over 255, because in color.h we convert it to an `int`.

`int rbyte = int(255.999 * r);`

Since a conversion from `double` to `int` truncates (does not round, just removes the decimal), it is set back to 255.

##### To Conclude:
255.999 is a deliberate hack to ensure `int(x * 255.999)` is part of [0, 255]

The .999 ensures rounding down even for x = 1.0, avoiding 256

## Cross Product
![Crossprod](../lagrida_latex_editor.png)
- The cross product gives a vector perpendicular to both U and V
- (u_2v_3 - v_2u_3) gives a scalar
- multiplying by unit vector i results in i being "scaled" by the result of (u_2v_3 - v_2u_3)
    - giving a "scaled" vector
- adding the "scaled" i+j+k gives the vector perpendicular to U and V