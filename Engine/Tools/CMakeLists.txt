
# spdlog

set(SPDLOG_3RDPARTY_DIR "3rdparty/spdlog")
set(SPDLOG_INCLUDE_DIR ${SPDLOG_INSTALL_DIR}/include)
add_subdirectory(${SPDLOG_3RDPARTY_DIR})

# crosswindow

set(CROSSWINDOW_3RDPARTY_DIR "3rdparty/crosswindow")
set(CROSSWINDOW_INCLUDE_DIR ${CROSSWINDOW_3RDPARTY_DIR}/src)
add_subdirectory(${CROSSWINDOW_3RDPARTY_DIR})

# glfw

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
set(GLFW_3RDPARTY_DIR "3rdparty/glfw")
set(GLFW_INCLUDE_DIR ${GLFW_3RDPARTY_DIR}/include)
add_subdirectory(${GLFW_3RDPARTY_DIR})

# stb

set(STB_3RDPARTY_DIR "3rdparty/stb")
set(STB_INCLUDE_DIR ${STB_3RDPARTY_DIR})

# Target Library

file(GLOB_RECURSE TOOLS_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)
list(FILTER TOOLS_SOURCES EXCLUDE REGEX "3rdparty/.*" )

file(GLOB_RECURSE TOOLS_MODULES CONFIGURE_DEPENDS
    *.cppm
)

add_library(LumineTools STATIC)
target_sources(LumineTools
    PUBLIC
        FILE_SET CXX_MODULES FILES
            ${TOOLS_MODULES}
    PRIVATE
        ${LUMINE_UTIL_HEADERS}
        ${TOOLS_SOURCES}
)
target_include_directories(LumineTools
    PUBLIC
        ${LUMINE_UTIL_INCLUDE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${SPDLOG_INCLUDE_DIR}
        ${CROSSWINDOW_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        ${STB_INCLUDE_DIR}
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
        SPDLOG_COMPILED_LIB
        LUMINE_WIN64=${LUMINE_WIN64}
        LUMINE_LINUX=${LUMINE_LINUX}
        STB_IMAGE_IMPLEMENTATION
)
