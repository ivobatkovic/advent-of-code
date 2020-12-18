cmake_minimum_required(VERSION 3.10)

project(day18)

include_directories(cpp/include)

find_package( Boost REQUIRED COMPONENTS regex )
include_directories( ${Boost_INCLUDE_DIRS} )


add_library(parser SHARED "cpp/src/parser.cpp")
target_include_directories(parser PUBLIC ${CMAKE_CURRENT_LIST_DIR}/cpp/include)
target_link_libraries(parser ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY})
# Set sources to be compiled
set( SOURCES "cpp/src/day18.cpp" )
add_library(day18.objs OBJECT ${SOURCES})
target_link_libraries(day18.objs parser)

# Give the relative path of the compilation as SOURCE_DIR
target_compile_definitions(day18.objs
                           PUBLIC SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

# Compile the sources
set( MAIN_SOURCES "cpp/src/main.cpp")
add_executable (${PROJECT_NAME} ${MAIN_SOURCES})

# Link potential libraries
target_link_libraries(${PROJECT_NAME} day18.objs)

# Build tests
set( TEST_SOURCES "cpp/src/test.cpp")
set ( TEST_TARGET ${PROJECT_NAME}_tests)

# Test exectuable
add_executable (${TEST_TARGET} ${TEST_SOURCES})
target_link_libraries(${TEST_TARGET} gtest gtest_main day18.objs)
set_target_properties(${TEST_TARGET} PROPERTIES EXCLUDE_FROM_ALL TRUE)

# Set up test
add_test( ${PROJECT_NAME}_test ${TEST_TARGET})
add_dependencies(build_tests ${TEST_TARGET})
