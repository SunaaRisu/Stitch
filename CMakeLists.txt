cmake_minimum_required(VERSION 3.10)
project(Stitch VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(glfw3 3.4 REQUIRED)

add_executable(Stitch main.cpp Stitch/Core/display.cpp Stitch/Core/display.h)
target_link_libraries(Stitch GL glfw)

set_property(TARGET Stitch PROPERTY CXX_STANDARD 23)
