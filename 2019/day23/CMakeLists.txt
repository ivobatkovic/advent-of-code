cmake_minimum_required(VERSION 3.10) 

project(day23)

# Include header files
include_directories(cpp/include)

# Set sources to be compiled
set( SOURCES "cpp/src/network.cpp" )
set( MAIN_SOURCES "cpp/src/main.cpp")

# Compile the sources
add_executable (${PROJECT_NAME} ${MAIN_SOURCES} ${SOURCES})

# Give the relative path of the compilation as SOURCE_DIR
target_compile_definitions(${PROJECT_NAME} 
                           PUBLIC SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
# Link intcode
target_link_libraries(${PROJECT_NAME} intcode)