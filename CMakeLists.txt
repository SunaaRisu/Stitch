cmake_minimum_required(VERSION 3.9)

project(stitch VERSION 1.0.0 DESCRIPTION "Stitch Game Engine" HOMEPAGE_URL "https://github.com/SunaaRisu/Stitch")

include(GNUInstallDirs)

add_library(stitch SHARED
  Stitch/src/Core/display.cpp
  Stitch/src/Renderer/shader.cpp
)

option(BUILD_UTILS OFF)
option(BUILD_SHARED_LIBS OFF)
add_compile_options(-fPIC)
add_subdirectory(Stitch/vendor/glew-2.2.0/build/cmake)
target_link_libraries(stitch glew_s)

include_directories(Stitch/vendor/glew-2.2.0/include)

add_subdirectory(Stitch/vendor/glfw)
target_link_libraries(stitch glfw)

set_target_properties(stitch PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  PUBLIC_HEADER Stitch/Stitch/include/Stitch/)

install(TARGETS stitch
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
