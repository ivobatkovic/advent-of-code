# Download and unpack boost at configure time
configure_file(cmake/boost_setup.in boost-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/boost-download )

if(result)
  message(FATAL_ERROR "CMake step for boost failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/boost-download )

if(result)
  message(FATAL_ERROR "Build step for boost failed: ${result}")
endif()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/boost-src
                 ${CMAKE_CURRENT_BINARY_DIR}/boost-build
                 EXCLUDE_FROM_ALL)        
include_directories(SYSTEM "${CMAKE_CURRENT_BINARY_DIR}/boost-src/libs/algorithm/include")
include_directories(SYSTEM "${CMAKE_CURRENT_BINARY_DIR}/boost-src/libs/regex/include")