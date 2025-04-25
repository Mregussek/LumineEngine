
function(Lumine_SetupVulkan3rdparty)
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

if(${LUMINE_WIN64})
	Lumine_SetupVulkan3rdparty()
endif()

add_subdirectory(src)
