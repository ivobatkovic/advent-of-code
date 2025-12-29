project(utils CXX)

find_package(Boost REQUIRED COMPONENTS regex)

add_library(utils "utils.cpp")
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(utils Boost::regex)

add_executable(utils-test "test_utils.cpp")
target_link_libraries(utils-test gtest gtest_main gmock_main utils)
set_target_properties(utils-test PROPERTIES OUTPUT_NAME "test")

add_test(NAME "test-utils" COMMAND $<TARGET_FILE:utils-test>)
add_dependencies(build_tests "utils-test")






