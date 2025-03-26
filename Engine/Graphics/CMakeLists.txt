
# Vulkan
find_package(Vulkan REQUIRED)
set(VULKAN_INCLUDE_DIR_LUMINE ${VULKAN_SDK}/include CACHE STRING "Vulkan Lumine Include Dir")

# Volk
set(VOLK_3RDPARTY_DIR 3rdparty/volk)
set(VOLK_INCLUDE_DIR_LUMINE 3rdparty/volk CACHE STRING "Volk Lumine 3rdparty Include Dir")
add_subdirectory(${VOLK_3RDPARTY_DIR})

# ------------------- GraphicsSRC

add_subdirectory(src)
