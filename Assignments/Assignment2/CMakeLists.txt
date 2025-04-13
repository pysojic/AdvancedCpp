cmake_minimum_required(VERSION 3.10.0)
project(Assigment2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Assignment2 11_3.cpp)

target_compile_options(Assignment2 PRIVATE -O0 -march=native)