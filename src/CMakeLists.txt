# Include the include file full of useful functions
# Argument: CMAKE_SOURCE_DIR
include(${CMAKE_SOURCE_DIR}/Include.cmake)

# Call the method to list CPP files recursively
include_sources(${CMAKE_CURRENT_SOURCE_DIR})