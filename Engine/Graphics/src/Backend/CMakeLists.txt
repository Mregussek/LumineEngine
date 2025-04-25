
add_subdirectory(Vulkan)

if(${LUMINE_WIN64})
    add_subdirectory(DirectX12)
endif()
