project(c-utils C)

add_library(cutilslib "c/c_utils.c")
target_include_directories(cutilslib PUBLIC "c/include")
