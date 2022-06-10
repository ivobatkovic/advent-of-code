project(utils C CXX)

add_library(c-utils "c/c_utils.c")
target_include_directories(c-utils PUBLIC "c/include")


add_library(cpp-utils "cpp/cpp_utils.cpp")
target_include_directories(cpp-utils PUBLIC "cpp/include")
