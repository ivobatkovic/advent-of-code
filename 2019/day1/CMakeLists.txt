cmake_minimum_required(VERSION 3.10)

project(day1)

# Get parent directory name
get_filename_component(year ../ ABSOLUTE)
get_filename_component(year "${year}" NAME)

# Prepare copying of test data
add_custom_target( ${year}-${PROJECT_NAME}-data
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
)


##### C++ Solutions Start #####

#############################

##### C Solutions Start #####
# Solution library
set( CSOURCES "c/solutions.c" )
add_library(csol OBJECT "c/solutions.c")
target_link_libraries(csol cutilslib)

add_executable(maint "c/main.c")
target_link_libraries(maint csol)
# Main file to call the solutions
##### C Solutions End #####
