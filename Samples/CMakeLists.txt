
add_executable(LumineSandbox)
target_sources(LumineSandbox
  PRIVATE
    main.cpp
)
target_link_libraries(LumineSandbox PRIVATE LumineTools LumineGraphics)
# target_compile_features(LumineSandbox PUBLIC cxx_std_23)
