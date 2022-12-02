project(utils C CXX)

include_directories("${CMAKE_SOURCE_DIR}")
add_library(c-utils "c_utils.c")
add_library(cpp-utils "cpp_utils.cpp")
