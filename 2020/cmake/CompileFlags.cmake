if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    set(COMPILER_FLAGS "-fstack-protector-all -fsanitize=undefined,address \
        -fPIC -O2 -pedantic-errors -Wall -Weffc++ -Werror -Wextra -Wshadow \
        -Wswitch-default")
    set(C_COMPILER_FLAGS "-std=c99")
    set(CXX_COMPILER_FLAGS "-std=c++14")
    #Since CMAKE uses -isysroot flag and these paths are ignored for Mac
    link_directories(/usr/local/lib)
    include_directories(/usr/local/include)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(COMPILER_FLAGS "-fstack-protector-all -fsanitize=undefined,address \
        -fPIC -O2 -Wall -Weffc++ -Werror -Wextra -Wshadow -pedantic-errors")
    set(C_COMPILER_FLAGS "-std=c99")
    set(CXX_COMPILER_FLAGS "-std=c++14")

    set(CXX_EFFECTIVE_CXX " -Wmissing-format-attribute -Wredundant-decls \
        -Wno-error=effc++ -Weffc++")
    set(CXX_WARNING_ALL   " -Wno-deprecated -Wall -Werror -Wshadow -Wextra \
        -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wpacked -Wcast-align \
        -Wchar-subscripts -Wcomment -Wdisabled-optimization -Wformat \
        -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k \
        -Wfloat-equal -Winit-self -Wno-error=inline -Winvalid-pch \
        -Wno-error=long-long -Wsign-compare -Wuninitialized -Wunreachable-code \
        -Wunsafe-loop-optimizations -Wunused -Wunused-function -Wunused-label \
        -Wunused-parameter -Wunused-but-set-parameter \
        -Wunused-but-set-variable -Wunused-value -Wunused-variable \
        -Wno-maybe-uninitialized -Wunused-result -Wmissing-braces \
        -Wmissing-field-initializers -Wmissing-format-attribute \
        -Wmissing-include-dirs -Wmissing-noreturn -Wparentheses -Wsign-compare \
        -Wswitch -Wuninitialized -Wunknown-pragmas -Wunreachable-code \
        -Wtrigraphs  -Wvariadic-macros -Wvolatile-register-var -Wwrite-strings \
        -Wpointer-arith -Wredundant-decls -Wreturn-type -Wsequence-point \
        -Wno-error=stack-protector -Wstrict-aliasing -Wstrict-aliasing=2 \
        -Wsync-nand -Warray-bounds -Wtrampolines -Wlogical-op -Wnormalized=nfc \
        -Wvarargs -Wvector-operation-performance -Wno-error=vla -Wtype-limits \
        -Wc++11-compat -Woverloaded-virtual -pedantic -Wcast-qual \
        -Wctor-dtor-privacy -Wpacked -Wswitch-enum -Wdouble-promotion \
        -Wmissing-declarations")
    set(CXX_WARNING_TO_FIX " -Wno-error=conversion -Wno-error=useless-cast \
    -Wno-error=old-style-cast -Wno-error=aggregate-return \
    -Wno-error=zero-as-null-pointer-constant \
    -Wno-error=deprecated-declarations -Wno-error=switch-default")
    set(CXX_COMPILER_FLAGS "${CXX_COMPILER_FLAGS} ${CXX_EFFECTIVE_CXX} \
    ${CXX_WARNING_ALL} ${CXX_WARNING_TO_FIX}")
    
endif()

set(CMAKE_C_FLAGS "${COMPILER_FLAGS} ${C_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMPILER_FLAGS} ${CXX_COMPILER_FLAGS}")
