# specifying a minimum CMake version
# establishes policy settings and ensures that the following CMake functions are run with a compatible version of CMake
cmake_minimum_required(VERSION 3.10)

# To start a project, we use the project() command to set the project name
# required with every project and should be called soon after cmake_minimum_required()
project(OutputImage)

# the add_executable(<name> <options>... <sources>...) command tells CMake to create an executable using the specified source code files.
add_executable(OutputImage main.cpp)



