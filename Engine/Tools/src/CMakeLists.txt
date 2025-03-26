
# Target Library

file(GLOB_RECURSE TOOLS_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)

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
        ${SPDLOG_INCLUDE_DIR_LUMINE}
        ${CROSSWINDOW_INCLUDE_DIR_LUMINE}
        ${GLFW_INCLUDE_DIR_LUMINE}
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
        LUMINE_USE_DIRECTX12=${LUMINE_USE_DIRECTX12}
        LUMINE_USE_VULKAN=${LUMINE_USE_VULKAN}
        LUMINE_WIN64=${LUMINE_WIN64}
        LUMINE_LINUX=${LUMINE_LINUX}
        SPDLOG_COMPILED_LIB
        STB_IMAGE_IMPLEMENTATION
)
