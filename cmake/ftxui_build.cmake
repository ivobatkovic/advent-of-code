# Download and unpack ftxui at configure time
configure_file(cmake/ftxui_setup.in ftxui-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ftxui-download )

if(result)
  message(FATAL_ERROR "CMake step for ftxui failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ftxui-download )

if(result)
  message(FATAL_ERROR "Build step for ftxui failed: ${result}")
endif()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/ftxui-src
                 ${CMAKE_CURRENT_BINARY_DIR}/ftxui-build
                 EXCLUDE_FROM_ALL)
           
message("${ftxui_SOURCE_DIR}")
include_directories(SYSTEM "${ftxui_SOURCE_DIR}/include")