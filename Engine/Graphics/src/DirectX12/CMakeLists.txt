
# Target Library

file(GLOB_RECURSE LUMINE_DX12_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)

file(GLOB_RECURSE LUMINE_DX12_MODULES CONFIGURE_DEPENDS
    *.cppm
)

add_library(Lumine_DirectX12 STATIC)
LumineSetLocalOptions(Lumine_DirectX12)
target_sources(Lumine_DirectX12
    PUBLIC
        FILE_SET CXX_MODULES FILES
            ${LUMINE_DX12_MODULES}
    PRIVATE
        ${LUMINE_UTIL_HEADERS}
        ${LUMINE_DX12_SOURCES}
)
target_include_directories(Lumine_DirectX12
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LUMINE_UTIL_INCLUDE_DIR}
)
target_link_libraries(Lumine_DirectX12
    PRIVATE
        Lumine_GraphicsCore
        LumineTools
        dxgi.lib
        d3d12.lib
        d3dcompiler.lib
)
target_compile_features(Lumine_DirectX12 PUBLIC cxx_std_23)
target_compile_definitions(Lumine_DirectX12
    PRIVATE
        LUMINE_WIN64=${LUMINE_WIN64}
        LUMINE_LINUX=${LUMINE_LINUX}
        LUMINE_RELEASE=${LUMINE_RELEASE}
        LUMINE_DEBUG=${LUMINE_DEBUG}
)
