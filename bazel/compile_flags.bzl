linker_flags = "-fstack-protector-all -fPIC -O2 -Wall -Weffc++ -Werror \
    -Wextra -Wshadow -pedantic-errors"
linux_extra_linker_flags = " -fsanitize=undefined,address"

compiler_flags = "-std=c++17 -Wmissing-format-attribute -Wredundant-decls \
    -Wno-error=effc++ -Weffc++ -Wno-deprecated -Wall -Werror -Wshadow -Wextra \
    -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wpacked -Wcast-align \
    -Wchar-subscripts -Wcomment -Wdisabled-optimization -Wformat -Wformat=2 \
    -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wfloat-equal \
    -Winit-self -Wno-error=inline -Winvalid-pch -Wno-error=long-long \
    -Wsign-compare -Wuninitialized -Wunreachable-code -Wunused \
    -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value \
    -Wunused-variable -Wunused-result -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-noreturn \
    -Wparentheses -Wsign-compare -Wswitch -Wuninitialized -Wunknown-pragmas \
    -Wunreachable-code -Wtrigraphs  -Wvariadic-macros -Wvolatile-register-var \
    -Wwrite-strings -Wpointer-arith -Wredundant-decls -Wreturn-type \
    -Wsequence-point -Wno-error=stack-protector -Wstrict-aliasing \
    -Wstrict-aliasing=2 -Warray-bounds  -Wvarargs  -Wno-error=vla \
    -Wtype-limits -Woverloaded-virtual -pedantic -Wcast-qual \
    -Wctor-dtor-privacy -Wpacked -Wswitch-enum -Wdouble-promotion \
    -Wmissing-declarations -Wno-error=conversion  -Wno-error=old-style-cast \
    -Wno-error=aggregate-return -Wno-error=zero-as-null-pointer-constant \
    -Wno-error=deprecated-declarations -Wno-error=switch-default"
linux_extra_compiler_flags = " -Wunsafe-loop-optimizations \
    -Wunused-but-set-parameter -Wunused-but-set-variable \
    -Wno-maybe-uninitialized -Wsync-nand -Wtrampolines -Wlogical-op \
    -Wnormalized=nfc -Wvector-operation-performance -Wno-error=useless-cast"

def get_compiler_flags():
    return select({
        "@platforms//os:osx":[compiler_flags],
        "//conditions:default": [compiler_flags + linux_extra_compiler_flags],
    })

def get_linker_flags():
    return select({
        "@platforms//os:osx":[linker_flags],
        "//conditions:default": [linker_flags + linux_extra_linker_flags],
    })