
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)


# Enable C++ modules
macro(LumineEnableCxxModules)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(FATAL_ERROR "C++ modules require MSVC or Clang with experimental support")
    endif()
    set(CMAKE_CXX_ENABLE_MODULE_STD ON)
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "Yes")
    # set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
    # set(CMAKE_CXX_MODULE_STD 1)
endmacro()
# -----------------


# IPO (Interprocedural Optimization)
macro(LumineEnableIPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT result OUTPUT output)
    if(result)
      set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
    else()
      message(SEND_ERROR "IPO is not supported: ${output}")
    endif()
endmacro()
# ---------------------------------


# Enhance error reporting and compiler messages
macro(LumineEnhanceErrorReportsAndCompilerMsgs)
    if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        if (WIN32)
            # On Windows cuda nvcc uses cl and not clang
            add_compile_options($<$<COMPILE_LANGUAGE:C>:-fcolor-diagnostics> $<$<COMPILE_LANGUAGE:CXX>:-fcolor-diagnostics>)
        else()
            add_compile_options(-fcolor-diagnostics)
        endif()
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        if (WIN32)
            # On Windows cuda nvcc uses cl and not gcc
            add_compile_options($<$<COMPILE_LANGUAGE:C>:-fdiagnostics-color=always>
                                $<$<COMPILE_LANGUAGE:CXX>:-fdiagnostics-color=always>)
        else()
            add_compile_options(-fdiagnostics-color=always)
        endif()
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND MSVC_VERSION GREATER 1900)
        add_compile_options(/diagnostics:column)
    else()
        message(STATUS "No colored compiler diagnostic set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
    endif()
endmacro()
# -------------------------------------------

macro(LumineSetLocalOptions targetName)
    add_library(${targetName}_Warnings INTERFACE)
    add_library(${targetName}_Options INTERFACE)

    include(${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake)
    myproject_set_project_warnings(
        ${targetName}_Warnings
        ${LUMINE_WARNINGS_AS_ERRORS}
        ""
        ""
        ""
        ""
    )

    include(${CMAKE_SOURCE_DIR}/cmake/StaticAnalyzers.cmake)
    myproject_enable_clang_tidy(${targetName}_Options ${LUMINE_WARNINGS_AS_ERRORS})

    target_compile_features(${targetName}_Options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})
endmacro()
