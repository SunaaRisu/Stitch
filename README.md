# Stitch
<p align="center">
  <img style="border-radius:50%" align="center" width="200" src="Resources/Branding/Stitch_Logo.webp" />

  <h1 align="center">Stitch</h1>
  <h3 align="center">"Game Engine"</h3>
</p>
<br/>

<!-- Badges -->
<p align="center">
  <a href="https://github.com/SunaaRisu/Stitch/issues">
    <img src="https://img.shields.io/github/issues/SunaaRisu/Stitch?style=flat-square">
  </a>

  <a href="https://github.com/SunaaRisu/Stitch/pulls">
    <img src="https://img.shields.io/github/issues-pr/SunaaRisu/Stitch?style=flat-square">
  </a>
</p>

# Welcome to the Stitch Wiki!

Stitch is a simple and VERY slowly growing "game engine" made by stitching together random code and hack solutions. :)

This is my first time doing something like this and feedback is very welcome. :3

If you want to use Stitch to do something with it, feel free to do so!!

# Development and Techstack

Stitch was developed and tested on Arch Linux. All other operating systems are not officially supported, but should compile as well, since no platform-specific code is used.

If you encounter any errors, please create an issue or suggest a solution.

Cmake is used as builder.

# Get Started

1. Add this repository to your project folder. <br/>
   This repository uses submodules to compile dependencies like glfw from source. <br/>
   You need to clone it recursively. `git clone --recursive https://github.com/SunaaRisu/Stitch` <br/>
   If the repository was cloned non-recursively previously, use `git submodule update --init --recursive` to clone the necessary submodules. <br/><br/>

2. Add Stitch to your Stitch to your Project and add `Stitch/include` to your include paths. <br/>
   Until I found a fix for this you also need to add `Stitch/Stitch/vendor/glew-2.2.0/include` to your include paths.

   In Cmake a simple setup might look something like this:
   ```cmake
   cmake_minimum_required(VERSION 3.10)
   project(example VERSION 0.1.0 LANGUAGES C CXX)

   add_subdirectory(Stitch)

   include_directories(Stitch/include)
   include_directories(Stitch/Stitch/vendor/glew-2.2.0/include)

   add_executable(example src/main.cpp)
   target_link_libraries(example stitch)

   set_property(TARGET example PROPERTY CXX_STANDARD 23)
   ```
   <br/>