
# Vulkan
find_package(Vulkan REQUIRED)

# Volk
set(VOLK_3RDPARTY_DIR 3rdparty/volk)
set(VOLK_INCLUDE_DIR 3rdparty/volk)
add_subdirectory(${VOLK_3RDPARTY_DIR})

# Target Library

file(GLOB_RECURSE GRAPHICS_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)
list(FILTER GRAPHICS_SOURCES EXCLUDE REGEX "3rdparty/.*" )

file(GLOB_RECURSE GRAPHICS_MODULES CONFIGURE_DEPENDS
    *.cppm
)

add_library(LumineGraphics)
target_sources(LumineGraphics
    PUBLIC
        FILE_SET CXX_MODULES FILES
            ${GRAPHICS_MODULES}
    PRIVATE
        ${LUMINE_UTIL_HEADERS}
        ${GRAPHICS_SOURCES}
)
target_include_directories(LumineGraphics
    PUBLIC
        ${LUMINE_UTIL_INCLUDE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${VULKAN_SDK}/include
        ${VOLK_INCLUDE_DIR}
)
target_link_libraries(LumineGraphics
    PUBLIC
        LumineTools
        volk_headers
)
target_compile_features(LumineGraphics PUBLIC cxx_std_23)
