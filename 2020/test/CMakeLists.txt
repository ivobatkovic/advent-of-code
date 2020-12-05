cmake_minimum_required(VERSION 3.10) 

project(test)

set(CMAKE_CXX_STANDARD 14)
# Set sources to be compiled
set( SOURCES "main.cpp" "test.cpp" )

# Compile the sources
add_executable (${PROJECT_NAME} ${SOURCES})

# Give the relative path of the compilation as SOURCE_DIR
target_compile_definitions(${PROJECT_NAME} 
                           PUBLIC SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")