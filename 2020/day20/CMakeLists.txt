cmake_minimum_required(VERSION 3.10)

project(day20)

include_directories(cpp/include)

add_library(jiggsaw SHARED "cpp/src/jiggsaw.cpp")
target_include_directories(jiggsaw PUBLIC ${CMAKE_CURRENT_LIST_DIR}/cpp/include)

# Set sources to be compiled
set( SOURCES "cpp/src/day20.cpp" )
add_library(day20.objs OBJECT ${SOURCES})
target_link_libraries(day20.objs jiggsaw)
# Give the relative path of the compilation as SOURCE_DIR
target_compile_definitions(day20.objs
                           PUBLIC SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

# Compile the sources
set( MAIN_SOURCES "cpp/src/main.cpp")
add_executable (${PROJECT_NAME} ${MAIN_SOURCES})

# Link potential libraries
target_link_libraries(${PROJECT_NAME} day20.objs)

# Build tests
set( TEST_SOURCES "cpp/src/test.cpp")
set ( TEST_TARGET ${PROJECT_NAME}_tests)

# Test exectuable
add_executable (${TEST_TARGET} ${TEST_SOURCES})
target_link_libraries(${TEST_TARGET} gtest gtest_main day20.objs)
set_target_properties(${TEST_TARGET} PROPERTIES EXCLUDE_FROM_ALL TRUE)

# Set up test
add_test( ${PROJECT_NAME}_test ${TEST_TARGET})
add_dependencies(build_tests ${TEST_TARGET})
