
# Target Library

file(GLOB_RECURSE GRAPHICS_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)

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
        ${VULKAN_INCLUDE_DIR_LUMINE}
        ${VOLK_INCLUDE_DIR_LUMINE}
)
target_link_libraries(LumineGraphics
    PUBLIC
        LumineTools
        volk_headers
)
target_compile_features(LumineGraphics PUBLIC cxx_std_23)
target_compile_definitions(LumineGraphics
    PRIVATE
        LUMINE_USE_DIRECTX12=${LUMINE_USE_DIRECTX12}
        LUMINE_USE_VULKAN=${LUMINE_USE_VULKAN}
        LUMINE_WIN64=${LUMINE_WIN64}
        LUMINE_LINUX=${LUMINE_LINUX}
)
