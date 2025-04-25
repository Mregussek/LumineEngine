
set(BUILD_MEDIA_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Media)
file(MAKE_DIRECTORY ${BUILD_MEDIA_DIR})

add_executable(LumineSandbox)
target_sources(LumineSandbox
  PRIVATE
    main.cpp
)
target_compile_features(LumineSandbox PUBLIC cxx_std_23)
target_compile_definitions(LumineSandbox
    PRIVATE
        LUMINE_USE_DIRECTX12=${LUMINE_USE_DIRECTX12}
        LUMINE_USE_VULKAN=${LUMINE_USE_VULKAN}
        LUMINE_WIN64=${LUMINE_WIN64}
        LUMINE_LINUX=${LUMINE_LINUX}
        LUMINE_RELEASE=${LUMINE_RELEASE}
        LUMINE_DEBUG=${LUMINE_DEBUG}
)
target_link_libraries(LumineSandbox
    PRIVATE
        LumineTools
        LumineGraphics
)

# Iterate over the list of media files
foreach(media_file IN LISTS LUMINE_MEDIA_FILES)
    # Set the destination path in the build directory
    get_filename_component(file_name ${media_file} NAME)
    set(FILE_DEST_PATH ${BUILD_MEDIA_DIR}/${file_name})

    # Add custom command to copy the file before build
    add_custom_command(
        TARGET LumineSandbox PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${media_file} ${FILE_DEST_PATH}
        COMMENT "Copying ${media_file} to ${FILE_DEST_PATH}"
    )
endforeach()
