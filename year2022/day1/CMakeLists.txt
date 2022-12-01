cmake_minimum_required(VERSION 3.10)

project(day1)

# Get parent directory name
get_filename_component(YEAR ../ ABSOLUTE)
get_filename_component(YEAR "${YEAR}" NAME)
include_directories("${CMAKE_SOURCE_DIR}")

set(DATA_FILES "${YEAR}-${PROJECT_NAME}-data")
add_custom_target(
  ${DATA_FILES}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data
          ${CMAKE_CURRENT_BINARY_DIR}/data)

# C++ setup start #####

# C++ solutions
set(CPP_SOURCES "cpp/solutions.cpp")
set(CPP_SOL "${YEAR}-${PROJECT_NAME}-cpp")

add_library(${CPP_SOL} ${CPP_SOURCES})
target_link_libraries(${CPP_SOL} cpp-utils)
target_include_directories(${CPP_SOL} PRIVATE "cpp/include" ${CMAKE_SOURCE_DIR})

# Main file for the c++ solution
set(CPP_MAIN_SOURCES "cpp/main.cpp")
set(CPP_MAIN "${YEAR}-${PROJECT_NAME}-cpp-main")

add_executable(${CPP_MAIN} ${CPP_MAIN_SOURCES})
add_dependencies(${CPP_MAIN} ${DATA_FILES})
set_target_properties(${CPP_MAIN} PROPERTIES OUTPUT_NAME "cpp-main")
target_link_libraries(${CPP_MAIN} ${CPP_SOL})
target_include_directories(${CPP_MAIN} PRIVATE "cpp/include")

# Test class for the c++ solution
set(CPP_TEST_SOURCES "cpp/test.cpp")
set(CPP_TEST "${YEAR}-${PROJECT_NAME}-cpp-test")

add_executable(${CPP_TEST} ${CPP_TEST_SOURCES})
add_dependencies(${CPP_TEST} ${DATA_FILES})
target_link_libraries(${CPP_TEST} gtest gtest_main ${CPP_SOL})
set_target_properties(${CPP_TEST_TARGET} PROPERTIES EXCLUDE_FROM_ALL TRUE)
target_include_directories(${CPP_TEST} PRIVATE "cpp/include")

# Set up test
set(CPP_TEST_TARGET "${YEAR}-${PROJECT_NAME}-cpp-tests")
add_test(${CPP_TEST_TARGET} ${YEAR}/${PROJECT_NAME}/${CPP_TEST})
set_property(TEST ${CPP_TEST_TARGET} PROPERTY WORKING_DIRECTORY
                                              ${CMAKE_BINARY_DIR})
add_dependencies(build_tests ${CPP_TEST})

# C++ setup stop ######

# ##############################################################################

# C setup start #######

# C++ solutions
set(C_SOURCES "c/solutions.c")
set(C_SOL "${YEAR}-${PROJECT_NAME}-c")

add_library(${C_SOL} ${C_SOURCES})
target_link_libraries(${C_SOL} c-utils)
target_include_directories(${C_SOL} PRIVATE "c/include" ${CMAKE_SOURCE_DIR})

# Main file for the c++ solution
set(C_MAIN_SOURCES "c/main.c")
set(C_MAIN "${YEAR}-${PROJECT_NAME}-c-main")

add_executable(${C_MAIN} ${C_MAIN_SOURCES})
add_dependencies(${C_MAIN} ${DATA_FILES})
set_target_properties(${C_MAIN} PROPERTIES OUTPUT_NAME "c-main")
target_link_libraries(${C_MAIN} ${C_SOL})
target_include_directories(${C_MAIN} PRIVATE "c/include")

# Test class for the c++ solution
set(C_TEST_SOURCES "c/test.cpp")
set(C_TEST "${YEAR}-${PROJECT_NAME}-c-test")

add_executable(${C_TEST} ${C_TEST_SOURCES})
add_dependencies(${C_TEST} ${DATA_FILES})
target_link_libraries(${C_TEST} gtest gtest_main ${C_SOL})
set_target_properties(${C_TEST_TARGET} PROPERTIES EXCLUDE_FROM_ALL TRUE)
target_include_directories(${C_TEST} PRIVATE "c/include")

# Set up test
set(C_TEST_TARGET "${YEAR}-${PROJECT_NAME}-c-tests")
add_test(${C_TEST_TARGET} ${YEAR}/${PROJECT_NAME}/${C_TEST})
set_property(TEST ${C_TEST_TARGET} PROPERTY WORKING_DIRECTORY
                                            ${CMAKE_BINARY_DIR})
add_dependencies(build_tests ${C_TEST})

# C setup stop ########
