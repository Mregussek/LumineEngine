# Enable C++ modules
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "C++ modules require MSVC or Clang with experimental support")
endif()

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "Yes")
