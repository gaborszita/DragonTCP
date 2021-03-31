cmake_minimum_required(VERSION 3.10)

project(DragonTCP VERSION 3.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(include)