# Graphics Programming

## Chapter 1
On Windows, you'd get the debug build from CMake running this command:
cmake -B build
cmake --build build

Then run your newly-built program like so:
`build\Debug\OutputImage.exe > image.ppm`

Later, it will be better to run optimized builds for speed. In that case, you would build like this:
`cmake --build build --config release`

and would run the optimized program like this:
`build\Release\OutputImage.exe > image.ppm`

### Loop explained:
- Outer for loop runs until `j = (image_height - 1)`
- Inner for loop runs until `i = (image_width - 1)`
- This means that only red or green values are incremented

### Why do we run `double(i) / (image_width - 1)`?
- i runs from 0 to image_width - 1
- Dividing by (image_width - 1) rescales this range into [0.0, 1.0]
    - if i=22, dividing it by 255, results in a decimal between 0.0 to 1.0


### Why do we divide i and j to get values of range [0.0, 1.0], only to multiply them again by 255.999?
- After dividing by width/height we end up with:
    ```
    r ∈ [0.0, 1.0]
    g ∈ [0.0, 1.0]
    b = 0.0
    ```
- If you change image_width to 512, i,j now runs 0–511
- using int(i) or int(j) would result in overflow (PPM expects color channels in [0, 255])