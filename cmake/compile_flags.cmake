set(CXX_COMPILER_FLAGS "-std=c++17 -Weffc++ -Wold-style-cast")
set(C_COMPILER_FLAGS "-std=c17 -Wstrict-prototypes")
string(
  CONCAT COMPILER_FLAGS
         "-fPIC -O2 -Wpedantic -pedantic-errors "
         "-Wall -Werror -Wextra -Waddress -Wfloat-equal -Wshadow "
         "-Wpointer-arith -Wcast-align -Wstrict-overflow=5 "
         "-Wwrite-strings -Wcast-qual -Wswitch-default "
         "-Wswitch-enum -Wconversion -Wunreachable-code ")

set(CMAKE_C_FLAGS "${COMPILER_FLAGS} ${C_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMPILER_FLAGS} ${CXX_COMPILER_FLAGS}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
    message(STATUS "Using Debug flags")
endif()

