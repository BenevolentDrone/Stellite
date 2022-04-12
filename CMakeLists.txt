# These two are like the header of the entire project, don't touch them
cmake_minimum_required(VERSION 3.0.0)
project(Stellite VERSION 0.1.0)

# These ones were included with cmake quickstart along with some others I managed to erase. Don't need them so far
#include(CTest)
#enable_testing()

# Following this tutorial
# https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
# the following two commands will automatically find and include the SDL2 into project
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Initialize an empty source file list into the global property
# Scope: global
# Property name: ALL_SOURCE_FILES
set_property(
    GLOBAL
    PROPERTY ALL_SOURCE_FILES)

# Following this tutorial
# https://www.youtube.com/watch?v=SYgESCQeGJY&list=PLK6MXr8gasrGmIiSuVQXpfFuE1uPT615s&index=8
add_subdirectory(include/glm)
add_subdirectory(src)

# Get the source file list after all subdirectories added their sources to it
# Target variable: SOURCE_FILES
# Scope: global
# Property name: ALL_SOURCE_FILES
get_property(
    SOURCE_FILES
    GLOBAL
    PROPERTY ALL_SOURCE_FILES)

# Debug message
#message(STATUS "Total source file list: ${SOURCE_FILES}")

# Add executable with all revelant source files
# Argument: SOURCE_FILES
add_executable(Stellite ${SOURCE_FILES})

# This one makes sure that CMakeLists specified with add_subdirectory lines propagate the include libraries to respective .h and .cpp files
target_link_libraries(Stellite SDL2)

#In case we need to know where the SDL2 lives
#message( ${SDL2_INCLUDE_DIRS} )