
set(LUMINE_GRAPHICS_UTILITIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Utilities"
    CACHE STRING "Graphics Utilities Dir"
)

set(LUMINE_GRAPHICS_SPECIFICATION_ADAPTER_H ${LUMINE_GRAPHICS_UTILITIES_DIR}/SpecificationAdapter.h
    CACHE STRING "Specification Adapter Header file"
)

add_subdirectory(Vulkan)

if(${LUMINE_WIN64})
    add_subdirectory(DirectX12)
endif()
