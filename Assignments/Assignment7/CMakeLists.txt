cmake_minimum_required(VERSION 3.10.0)
project(Assigment7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-14")

include_directories(include)

add_executable(Assignment7_1_2_3 17_1_2_3.cpp)

target_compile_options(Assignment7_1_2_3 PRIVATE -O0 -march=native)
