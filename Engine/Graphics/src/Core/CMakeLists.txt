
# Target Library

file(GLOB_RECURSE LUMINE_CORE_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)

file(GLOB_RECURSE LUMINE_CORE_MODULES CONFIGURE_DEPENDS
    *.cppm
)

add_library(Lumine_GraphicsCore STATIC)
LumineSetLocalOptions(Lumine_GraphicsCore)
target_sources(Lumine_GraphicsCore
    PUBLIC
        FILE_SET CXX_MODULES FILES
            ${LUMINE_CORE_MODULES}
    PRIVATE
        ${LUMINE_UTIL_HEADERS}
        ${LUMINE_CORE_SOURCES}
)
target_include_directories(Lumine_GraphicsCore
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LUMINE_UTIL_INCLUDE_DIR}
)
target_link_libraries(Lumine_GraphicsCore
    PRIVATE
        LumineTools
)
target_compile_features(Lumine_GraphicsCore PUBLIC cxx_std_23)
target_compile_definitions(Lumine_GraphicsCore
    PRIVATE
        LUMINE_WIN64=${LUMINE_WIN64}
        LUMINE_LINUX=${LUMINE_LINUX}
        LUMINE_RELEASE=${LUMINE_RELEASE}
        LUMINE_DEBUG=${LUMINE_DEBUG}
)
