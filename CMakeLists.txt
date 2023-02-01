cmake_minimum_required(VERSION 3.23.2)

project(IT8951 VERSION 1.0)

# C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# subdirectories
add_subdirectory(lib)
add_subdirectory(example/Bcm)