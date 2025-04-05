cmake_minimum_required(VERSION 3.10)
project(Lecture_12 CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(wind wind.cpp)
add_executable(indent_stream TestIndentStream.cpp indentStream.cpp)
add_executable(variadic_examples variadic_examples.cpp)
add_executable(Tuple Tuple.cpp)