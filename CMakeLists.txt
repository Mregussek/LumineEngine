
cmake_minimum_required(VERSION 3.31)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# ------------------- Build Media / Resources Setup

set(LUMINE_MEDIA_FILES
    ${CMAKE_SOURCE_DIR}/Media/lumine.ico
    ${CMAKE_SOURCE_DIR}/Media/lumine.png
    CACHE STRING "All Lumine Media Files"
)

# ------------------- C++ setup

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

project(LumineEngine
    VERSION 0.0.1
    DESCRIPTION "Lumine Engine"
    HOMEPAGE_URL "https://github.com/Mregussek/LumineEngine"
    LANGUAGES CXX C
)

include(cmake/StandardSettings.cmake)

LumineEnableCxxModules()
LumineEnhanceErrorReportsAndCompilerMsgs()

# ------------------- Project Source

add_subdirectory(Engine)
add_subdirectory(Sandbox)
