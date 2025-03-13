
file(GLOB_RECURSE TOOLS_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)

set(TOOLS_MODULES Tools.cppm)

add_library(LumineTools)
target_sources(LumineTools
    PUBLIC
        FILE_SET CXX_MODULES FILES
            ${TOOLS_MODULES}
    PRIVATE
        ${TOOLS_SOURCES}
)
target_compile_features(LumineTools PUBLIC cxx_std_23)
