cmake_minimum_required(VERSION 3.10)

project(adventofcode)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Configuring with Release mode")
    set(CMAKE_BUILD_TYPE "Release")
endif (NOT CMAKE_BUILD_TYPE)


set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE INTERNAL "") # works

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake"
                      ${CMAKE_MODULE_PATH})

# Configure third-party dependencies
include(cmake/gtest_build.cmake)

# Compilation flags to be used on the projects
include(cmake/compile_flags.cmake)

# Enable testing for directories containing the solutions to day 1 through 25
enable_testing()

# Define a custom target for building the tests
add_custom_target(build_tests)

# Find all sub folders containing CMakeLists.txt
macro(SUBDIRLIST result dir)
  file(
    GLOB children
    RELATIVE ${dir}
    ${dir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${dir}/${child} AND EXISTS ${dir}/${child}/CMakeLists.txt)
      list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

# Add all subdirectories with CMakeLists.txt
subdirlist(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
foreach(subdir ${SUBDIRS})
  add_subdirectory(${subdir})
endforeach()

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)
