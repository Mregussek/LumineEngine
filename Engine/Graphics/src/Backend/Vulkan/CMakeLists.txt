
# Target Library

file(GLOB_RECURSE LUMINE_VK_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)

file(GLOB_RECURSE LUMINE_VK_MODULES CONFIGURE_DEPENDS
    *.cppm
)

add_library(Lumine_Vulkan STATIC)
LumineSetLocalOptions(Lumine_Vulkan)
target_sources(Lumine_Vulkan
    PUBLIC
        FILE_SET CXX_MODULES FILES
            ${LUMINE_VK_MODULES}
    PRIVATE
        ${LUMINE_UTIL_HEADERS}
        ${LUMINE_VK_SOURCES}
)
target_include_directories(Lumine_Vulkan
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LUMINE_UTIL_INCLUDE_DIR}
        ${VULKAN_INCLUDE_DIR_LUMINE}
)
target_link_libraries(Lumine_Vulkan
    PRIVATE
        LumineTools
        volk_headers
)
target_compile_features(Lumine_Vulkan PUBLIC cxx_std_23)
target_compile_definitions(Lumine_Vulkan
    PRIVATE
        LUMINE_WIN64=${LUMINE_WIN64}
        LUMINE_LINUX=${LUMINE_LINUX}
        LUMINE_RELEASE=${LUMINE_RELEASE}
        LUMINE_DEBUG=${LUMINE_DEBUG}
)
