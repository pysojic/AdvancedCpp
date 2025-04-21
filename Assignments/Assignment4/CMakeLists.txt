cmake_minimum_required(VERSION 3.10.0)
project(Assigment4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Assignment4_1 14_1.cpp)
add_executable(Assignment4_2 14_2.cpp)
# add_executable(Assignment3_3 12_3.cpp)
# add_executable(Assignment3_4 12_4.cpp)

target_compile_options(Assignment4_1 PRIVATE -O0 -march=native)
target_compile_options(Assignment4_2 PRIVATE -O0 -march=native)
# target_compile_options(Assignment3_3 PRIVATE -O0 -march=native)
# target_compile_options(Assignment3_4 PRIVATE -O0 -march=native)