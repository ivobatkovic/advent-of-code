cmake_minimum_required(VERSION 3.10) 

project(iolib)

# set source files
set(src ${CMAKE_CURRENT_SOURCE_DIR}/cpp/src/utils.cpp)
		
# define library target
add_library(iolib SHARED ${src})
target_include_directories(iolib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/cpp/include)