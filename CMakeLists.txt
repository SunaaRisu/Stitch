cmake_minimum_required(VERSION 3.9)

project(stitch VERSION 1.0.0 DESCRIPTION "Stitch Game Engine" HOMEPAGE_URL "https://github.com/SunaaRisu/Stitch")

include(GNUInstallDirs)

add_library(stitch
  Stitch/src/Core/display.cpp
  Stitch/src/Renderer/shader.cpp
)

add_subdirectory(Stitch/vendor/glfw)
target_link_libraries(stitch glfw)

set_target_properties(stitch PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  PUBLIC_HEADER Stitch/include/stitch.h)

install(TARGETS stitch
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
