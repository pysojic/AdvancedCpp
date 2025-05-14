cmake_minimum_required(VERSION 3.10)
project(Assignment6 LANGUAGES CXX)

# ——————————————
# Compiler & Standard
# ——————————————
set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-14")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ——————————————
# Import studxml (pre-built)
# ——————————————
set(STUDXML_ROOT "${CMAKE_SOURCE_DIR}/libstudxml-1.0.1")
add_library(studxml STATIC IMPORTED)
set_target_properties(studxml PROPERTIES
  IMPORTED_LOCATION
    "${STUDXML_ROOT}/xml/.libs/libstudxml.a"
  INTERFACE_INCLUDE_DIRECTORIES
    "${STUDXML_ROOT}"
)

# ——————————————
# Your sources
# ——————————————
set(SRC_FILES
  "${CMAKE_SOURCE_DIR}/driver.cpp"
  "${CMAKE_SOURCE_DIR}/IndentStream.cpp"
  "${CMAKE_SOURCE_DIR}/fmt/format.cc"
)

add_executable(xsd2cpp ${SRC_FILES})

# ——————————————
# Include paths
# ——————————————
target_include_directories(xsd2cpp PRIVATE
  "${CMAKE_SOURCE_DIR}"           # so “#include <fmt/format-inl.h>” finds fmt/…
  "${CMAKE_SOURCE_DIR}/include"   # so “#include <foo.h>” finds include/foo.h
)

# ——————————————
# Compile & link
# ——————————————
target_compile_options(xsd2cpp PRIVATE
  -O0 -march=native
)
target_link_libraries(xsd2cpp PRIVATE
  studxml
)
