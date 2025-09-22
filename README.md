# Graphics Programming

On Windows, you'd get the debug build from CMake running this command:

```cmake -B build```

```cmake --build build```

Then run your newly-built program like so:
`build\Debug\OutputImage.exe > image.ppm`

Later, it will be better to run optimized builds for speed. In that case, you would build like this:
`cmake --build build --config release`

and would run the optimized program like this:
`build\Release\OutputImage.exe > image.ppm`

# Chapters
Each chapter has its own README.md file which specifies the learning outcomes and notes. You can find this in Chapter#/projectName/README.md

