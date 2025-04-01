cmake_minimum_required(VERSION 3.10.0)
project(AdvCppHmw1 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AdvCppHmw1 10_3.cpp)

target_include_directories(AdvCppHmw1 PRIVATE "/Users/py/Documents/GitHub/libs/compile-time-regular-expressions/single-header")
target_include_directories(AdvCppHmw1 PRIVATE "/Users/py/Documents/UChicago/Courses/Spring_2025/Advanced C++/Utilities")

target_compile_options(AdvCppHmw1 PRIVATE -O0 -march=native) # Use for debug: -O0 -g -Wall -Wextra -Wpedantic
