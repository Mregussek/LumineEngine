
file(GLOB_RECURSE GRAPHICS_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)

set(GRAPHICS_MODULES Graphics.cppm)

add_library(LumineGraphics)
target_sources(LumineGraphics
    PUBLIC
        FILE_SET CXX_MODULES FILES
            ${GRAPHICS_MODULES}
    PRIVATE
        ${GRAPHICS_SOURCES}
)
target_link_libraries(LumineGraphics PUBLIC LumineTools)
target_compile_features(LumineGraphics PUBLIC cxx_std_23)
