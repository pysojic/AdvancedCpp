cmake_minimum_required(VERSION 3.10.0)
project(Assigment3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Assignment3_1 12_1.cpp)
add_executable(Assignment3_2 12_2.cpp)
add_executable(Assignment3_3 12_3.cpp)

target_compile_options(Assignment3_1 PRIVATE -O0 -march=native)
target_compile_options(Assignment3_2 PRIVATE -O0 -march=native)
target_compile_options(Assignment3_3 PRIVATE -O0 -march=native)