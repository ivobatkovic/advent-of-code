#!/bin/bash

# Append where to start looking from
if [ $# -eq 0 ]; then start="."
    else start=$1
fi

source_files=$(find $start -type f \( -iname \*.cpp -o -iname \*.c \))
header_files=$(find $start -type f \( -iname \*.hpp -o -iname \*.h \))
for f in $source_files $header_files; do
    clang-format --verbose -sort-includes -i $f
done
echo Done formatting
