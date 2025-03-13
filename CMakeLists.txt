# ------------------- Default Setup

cmake_minimum_required(VERSION 3.30)
project(LumineEngine LANGUAGES CXX)

# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_MODULE_STD TRUE)  # Enable 'import std;' [3]

# Enable C++ modules
include(cmake/modules.cmake)

# ------------------- Some Info display

message(STATUS "Binary Dir: ${CMAKE_BINARY_DIR}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CXX Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Project Dir: ${PROJECT_SOURCE_DIR}")

# ------------------- Loading all projects

add_subdirectory(Engine)
add_subdirectory(Samples)
