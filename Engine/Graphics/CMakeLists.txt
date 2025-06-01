
function(Lumine_Setup3rdpartyVulkan)
	# Vulkan
	find_package(Vulkan REQUIRED)
	set(VULKAN_INCLUDE_DIR_LUMINE ${VULKAN_SDK}/include CACHE STRING "Vulkan Lumine Include Dir")
	message(STATUS "--- VULKAN_INCLUDE_DIR_LUMINE: ${VULKAN_INCLUDE_DIR_LUMINE}")
	
	# Volk
	set(VOLK_3RDPARTY_DIR 3rdparty/volk)
	set(VOLK_INCLUDE_DIR_LUMINE ${CMAKE_SOURCE_DIR}/Engine/Graphics/3rdparty/volk CACHE STRING "Volk Lumine 3rdparty Include Dir")
	add_subdirectory(${VOLK_3RDPARTY_DIR})
	message(STATUS "--- VOLK_INCLUDE_DIR_LUMINE: ${VOLK_INCLUDE_DIR_LUMINE}")
endfunction()

function(Lumine_Setup3rdpartyDX12)
	# DirectX-Headers
	set(DXHEADERS_3RDPARTY_DIR 3rdparty/DirectX-Headers)
	set(DXHEADERS_INCLUDE_DIR_LUMINE ${CMAKE_SOURCE_DIR}/Engine/Graphics/3rdparty/DirectX-Headers/include CACHE STRING "DirectX-Headers Lumine 3rdparty Include Dir")
	add_subdirectory(${DXHEADERS_3RDPARTY_DIR})
	message(STATUS "--- DXHEADERS_INCLUDE_DIR_LUMINE: ${DXHEADERS_INCLUDE_DIR_LUMINE}")
endfunction()

if(${LUMINE_WIN64})
	Lumine_Setup3rdpartyVulkan()
	Lumine_Setup3rdpartyDX12()
endif()

add_subdirectory(src)
