cmake_minimum_required(VERSION 3.10) 

project(test)

set(CMAKE_CXX_STANDARD 14)
# Set sources to be compiled
file(GLOB SOURCES "*.cpp")

# Compile the sources
add_executable (${PROJECT_NAME} ${SOURCES})
