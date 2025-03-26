# spdlog

set(SPDLOG_3RDPARTY_DIR 3rdparty/spdlog)
set(SPDLOG_INCLUDE_DIR_LUMINE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/spdlog/include CACHE STRING "spdlog Lumine Include Dir")
add_subdirectory(${SPDLOG_3RDPARTY_DIR})
message(STATUS "--- SPDLOG_INCLUDE_DIR_LUMINE: ${SPDLOG_INCLUDE_DIR_LUMINE}")

# crosswindow

set(CROSSWINDOW_3RDPARTY_DIR 3rdparty/crosswindow)
set(CROSSWINDOW_INCLUDE_DIR_LUMINE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/crosswindow/src CACHE STRING "CrossWindow Lumine Include Dir")
add_subdirectory(${CROSSWINDOW_3RDPARTY_DIR})
message(STATUS "--- CROSSWINDOW_INCLUDE_DIR_LUMINE: ${CROSSWINDOW_INCLUDE_DIR_LUMINE}")

# glfw

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
set(GLFW_3RDPARTY_DIR 3rdparty/glfw)
set(GLFW_INCLUDE_DIR_LUMINE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw/include CACHE STRING "Glfw Lumine Include Dir")
add_subdirectory(${GLFW_3RDPARTY_DIR})
message(STATUS "--- GLFW_INCLUDE_DIR_LUMINE: ${GLFW_INCLUDE_DIR_LUMINE}")

# stb

set(STB_3RDPARTY_DIR 3rdparty/stb)
set(STB_INCLUDE_DIR_LUMINE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb CACHE STRING "stb Lumine Include Dir")
message(STATUS "--- STB_INCLUDE_DIR_LUMINE: ${STB_INCLUDE_DIR_LUMINE}")

# ------------------- ToolsSRC

add_subdirectory(src)
