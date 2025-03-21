
cmake_minimum_required(VERSION 3.31)

# ------------------- C++ modules

include(cmake/modules.cmake)

# ------------------- Build Media / Resources Setup

set(LUMINE_MEDIA_FILES
    ${CMAKE_SOURCE_DIR}/Media/lumine.ico
    ${CMAKE_SOURCE_DIR}/Media/lumine.png
    CACHE STRING "All Lumine Media Files"
)

# ------------------- Project

project(LumineEngine LANGUAGES CXX)

add_subdirectory(Engine)
add_subdirectory(Sandbox)
