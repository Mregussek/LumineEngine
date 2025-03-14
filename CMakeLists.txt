
cmake_minimum_required(VERSION 3.31)

# ------------------- C++ modules

include(cmake/modules.cmake)

# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
# set(CMAKE_CXX_MODULE_STD TRUE)

# ------------------- Project

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(LumineEngine LANGUAGES CXX)

add_subdirectory(Engine)
add_subdirectory(Samples)
