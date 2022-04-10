cmake_minimum_required(VERSION 3.0.0)
project(Stellite VERSION 0.1.0)

include(CTest)
enable_testing()

# Following this tutorial
# https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
# the following two commands will automatically find and include the SDL2 into project
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Stellite main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
