set(CXX_COMPILER_FLAGS "-std=c++20 -Weffc++ -Wold-style-cast")
string(
  CONCAT COMPILER_FLAGS
         "-fPIC -O2 -Wpedantic -pedantic-errors "
         "-Wall -Werror -Wextra -Waddress -Wfloat-equal -Wshadow "
         "-Wpointer-arith -Wcast-align -Wstrict-overflow=5 "
         "-Wwrite-strings -Wcast-qual -Wswitch-default "
         "-Wswitch-enum -Wconversion -Wunreachable-code ")

set(CMAKE_CXX_FLAGS "${COMPILER_FLAGS} ${CXX_COMPILER_FLAGS}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
    message(STATUS "Using Debug flags")
endif()

