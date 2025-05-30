﻿
# Target Library

file(GLOB_RECURSE TOOLS_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)

file(GLOB_RECURSE TOOLS_MODULES CONFIGURE_DEPENDS
    *.cppm
)

add_library(LumineTools STATIC)
LumineSetLocalOptions(LumineTools)
target_sources(LumineTools
    PUBLIC
        FILE_SET CXX_MODULES FILES
            ${TOOLS_MODULES}
    PRIVATE
        ${LUMINE_UTIL_HEADERS}
        ${TOOLS_SOURCES}
)
target_include_directories(LumineTools
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LUMINE_UTIL_INCLUDE_DIR}
        ${STB_INCLUDE_DIR_LUMINE}
)
target_link_libraries(LumineTools
    PRIVATE
        spdlog::spdlog
        CrossWindow
        glfw
)
target_compile_features(LumineTools PUBLIC cxx_std_23)
target_compile_definitions(LumineTools
    PRIVATE
        LUMINE_WIN64=${LUMINE_WIN64}
        LUMINE_LINUX=${LUMINE_LINUX}
        LUMINE_RELEASE=${LUMINE_RELEASE}
        LUMINE_DEBUG=${LUMINE_DEBUG}
        STB_IMAGE_IMPLEMENTATION
)
