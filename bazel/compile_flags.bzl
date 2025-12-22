cxx_compiler_flags = " -std=c++20 -Weffc++ -Wold-style-cast"
compiler_flags = "-fPIC -O2 -Wpedantic -pedantic-errors \
    -Wall -Werror -Wextra -Waddress -Wfloat-equal -Wshadow \
    -Wpointer-arith -Wcast-align -Wstrict-overflow=5 \
    -Wwrite-strings -Wcast-qual -Wswitch-default \
    -Wswitch-enum -Wconversion -Wunreachable-code" 

def get_cxx_compiler_flags():
    return [compiler_flags + cxx_compiler_flags]
