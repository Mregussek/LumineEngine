# cmake/FindClangTidy.cmake
include_guard(GLOBAL)

# Common exe names
set(CLANG_TIDY_NAMES
    clang-tidy
    clang-tidy-18
    clang-tidy-17
    clang-tidy-16
    clang-tidy-15
    clang-tidy-14
    clang-tidy.exe
)

# Common installation paths
set(CLANG_TIDY_SEARCH_PATHS
    # Windows
    "C:/Program Files/LLVM/bin"
    "C:/Program Files (x86)/LLVM/bin"
    "C:/Program Files/Microsoft Visual Studio/*/Enterprise/VC/Tools/Llvm/bin"
    "C:/Program Files/Microsoft Visual Studio/*/Professional/VC/Tools/Llvm/bin"
    "C:/Program Files/Microsoft Visual Studio/*/Community/VC/Tools/Llvm/bin"
    
    # Linux
    "/usr/bin"
    "/usr/local/bin"
    "/opt/llvm/bin"
    
    # macOS
    "/usr/local/opt/llvm/bin"
    "/opt/homebrew/opt/llvm/bin"
)

find_program(CLANG_TIDY
    NAMES ${CLANG_TIDY_NAMES}
    PATHS ${CLANG_TIDY_SEARCH_PATHS}
    DOC "Path to clang-tidy executable"
)

if(CLANG_TIDY)
    # Validate clang-tidy works
    execute_process(
        COMMAND ${CLANG_TIDY} --version
        OUTPUT_QUIET
        ERROR_QUIET
        RESULT_VARIABLE CLANG_TIDY_VALID
    )
    
    if(NOT CLANG_TIDY_VALID EQUAL 0)
        message(WARNING "Found clang-tidy but validation failed: ${CLANG_TIDY}")
        set(CLANG_TIDY CLANG_TIDY-NOTFOUND)
    else()
        # Get version for diagnostics
        execute_process(
            COMMAND ${CLANG_TIDY} --version
            OUTPUT_VARIABLE CLANG_TIDY_VERSION_OUTPUT
        )
        string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" CLANG_TIDY_VERSION ${CLANG_TIDY_VERSION_OUTPUT})
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ClangTidy
    REQUIRED_VARS CLANG_TIDY
    VERSION_VAR CLANG_TIDY_VERSION
    FOUND_VAR ClangTidy_FOUND
)

mark_as_advanced(CLANG_TIDY)
