cmake_minimum_required(VERSION 3.10) 

project(adventofcode)

SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})

# Download and unpack googletest at configure time
configure_file(cmake/gtest_setup.cmake googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Compilation flags to be used on the projects
INCLUDE (cmake/CompileFlags.cmake)
include_directories(utils/cpp/include)

# Enable testing for directories containing the solutions to day 1 through 25
enable_testing()

# Define a custom target for building the tests
add_custom_target(build_tests)

# Find all sub folders containing CMakeLists.txt
MACRO(SUBDIRLIST result dir)
  FILE(GLOB children RELATIVE ${dir} ${dir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${dir}/${child} AND EXISTS ${dir}/${child}/CMakeLists.txt)
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

# Add all subdirectories with CMakeLists.txt
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
FOREACH(subdir ${SUBDIRS})
  add_subdirectory(${subdir})
ENDFOREACH()