
cmake_minimum_required(VERSION 3.31)

# ------------------- C++ setup

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# ------------------- Build Media / Resources Setup

set(LUMINE_MEDIA_FILES
    ${CMAKE_SOURCE_DIR}/Media/lumine.ico
    ${CMAKE_SOURCE_DIR}/Media/lumine.png
    CACHE STRING "All Lumine Media Files"
)

# ------------------- Project

project(LumineEngine LANGUAGES CXX)

add_subdirectory(Engine)
add_subdirectory(Sandbox)

# ------------------- Project

if(${LUMINE_CMAKE_USE_CLANG_TIDY})
    find_package(ClangTidy)
    find_package(Python3 REQUIRED)

    if(${ClangTidy_FOUND} AND ${Python3_FOUND})
        set(FILTERED_COMPILE_COMMANDS "${CMAKE_BINARY_DIR}/compile_commands_filtered.json")
        set(CLANG_TIDY_STAMP "${CMAKE_BINARY_DIR}/clang_tidy.stamp")

        add_custom_command(
            OUTPUT ${FILTERED_COMPILE_COMMANDS}
            COMMAND ${Python3_EXECUTABLE}
                ${CMAKE_SOURCE_DIR}/Scripts/filter_compile_commands.py
                -i ${CMAKE_BINARY_DIR}/compile_commands.json
                -o ${FILTERED_COMPILE_COMMANDS}
                -e 3rdparty
            DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
            COMMENT "Filtering 3rdparty code from compile commands"
            VERBATIM
        )

        add_custom_command(
            OUTPUT ${CLANG_TIDY_STAMP}
            COMMAND ${CLANG_TIDY}
                -p ${FILTERED_COMPILE_COMMANDS}
                --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
                ${CMAKE_SOURCE_DIR}/Engine/Graphics/src/*.cpp
            COMMAND ${CMAKE_COMMAND} -E touch ${CLANG_TIDY_STAMP}  # Create stamp file
            DEPENDS ${FILTERED_COMPILE_COMMANDS}
            COMMENT "Running clang-tidy checks"
            VERBATIM
        )

        add_custom_target(clang_tidy_all
            DEPENDS ${CLANG_TIDY_STAMP}
        )

    else()
        message(WARNING "clang-tidy or Python not found - analysis target disabled")
    endif()

endif()
