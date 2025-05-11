
add_subdirectory(Core)
add_subdirectory(Vulkan)

if(${LUMINE_WIN64})
    add_subdirectory(DirectX12)
endif()

# Target Library

set(GRAPHICS_SOURCES GLogger.h GraphicsFactory.cpp)
set(GRAPHICS_MODULES GraphicsFactory.cppm GraphicsBackend.cppm)

add_library(LumineGraphics STATIC)
LumineSetLocalOptions(LumineGraphics)
target_sources(LumineGraphics
    PUBLIC
        FILE_SET CXX_MODULES FILES
            ${GRAPHICS_MODULES}
    PRIVATE
        ${LUMINE_UTIL_HEADERS}
        ${GRAPHICS_SOURCES}
)
target_include_directories(LumineGraphics
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LUMINE_UTIL_INCLUDE_DIR}
)
target_compile_features(LumineGraphics PUBLIC cxx_std_23)
target_compile_definitions(LumineGraphics
    PRIVATE
        LUMINE_USE_DIRECTX12=${LUMINE_USE_DIRECTX12}
        LUMINE_USE_VULKAN=${LUMINE_USE_VULKAN}
        LUMINE_WIN64=${LUMINE_WIN64}
        LUMINE_LINUX=${LUMINE_LINUX}
        LUMINE_RELEASE=${LUMINE_RELEASE}
        LUMINE_DEBUG=${LUMINE_DEBUG}
)

target_link_libraries(LumineGraphics
    PRIVATE
        Lumine_GraphicsCore
        Lumine_Vulkan
        LumineTools
)
if(${LUMINE_WIN64})
    target_link_libraries(LumineGraphics
        PRIVATE
            Lumine_DirectX12
    )
endif()
