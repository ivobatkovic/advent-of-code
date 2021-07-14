cmake_minimum_required(VERSION 3.10)

project(day23)

# Get parent directory name
get_filename_component(year ../ ABSOLUTE)
get_filename_component(year "${year}" NAME)

# Get root directory
include_directories(${CMAKE_SOURCE_DIR})

# Set sources to be compiled
set( SOURCES "cpp/src/network.cpp" )
add_library(day23_${year}.objs OBJECT ${SOURCES})
link_libraries(day23_${year}.objs intcode)

# Give the relative path of the compilation as SOURCE_DIR
target_compile_definitions(day23_${year}.objs
                           PUBLIC SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

# Compile the sources
set( MAIN_SOURCES "cpp/src/main.cpp")
add_executable (${PROJECT_NAME}_${year} ${MAIN_SOURCES})

# Link potential libraries
target_link_libraries(${PROJECT_NAME}_${year} day23_${year}.objs)