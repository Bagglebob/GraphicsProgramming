# Graphics Programming

## Chapter #2
On Windows, you'd get the debug build from CMake running this command:

```cmake -B build```

```cmake --build build```

Then run your newly-built program like so:
`build\Debug\OutputImage.exe > image.ppm`

Later, it will be better to run optimized builds for speed. In that case, you would build like this:
`cmake --build build --config release`

and would run the optimized program like this:
`build\Release\OutputImage.exe > image.ppm`

## Chapter #3: The vec3 Class

- We'll use the same class vec3 for colors, locations, directions, offsets
- Some people don't like this because it doesn't prevent you from doing something silly, like subtracting a position from a color. 

- we declare two aliases for vec3: point3 and color to differentiate

