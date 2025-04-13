cmake_minimum_required(VERSION 3.10.0)
project(Assigment3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Assignment3 11_3.cpp)

target_compile_options(Assignment3 PRIVATE -O0 -march=native)