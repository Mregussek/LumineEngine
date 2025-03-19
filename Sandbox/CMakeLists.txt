
add_executable(LumineSandbox)
target_sources(LumineSandbox
  PRIVATE
    main.cpp
)
target_link_libraries(LumineSandbox PRIVATE LumineTools LumineGraphics)
target_compile_features(LumineSandbox PUBLIC cxx_std_23)
target_compile_definitions(LumineSandbox
    PRIVATE
        LUMINE_USE_DIRECTX12=${LUMINE_USE_DIRECTX12}
        LUMINE_USE_VULKAN=${LUMINE_USE_VULKAN}
)
