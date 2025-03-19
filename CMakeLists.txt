
cmake_minimum_required(VERSION 3.31)

# ------------------- C++ modules

include(cmake/modules.cmake)

# ------------------- Project

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(LumineEngine LANGUAGES CXX)

add_subdirectory(Engine)
add_subdirectory(Sandbox)
