#!/bin/bash

# Append where to start looking from
if [ $# -eq 0 ]; then
    folders=$(git ls-files '*.cpp' '*.h' | awk -F/ '{print $1}' | sort -u)
    # Map string "folder1\nfolder2\n..." to an array [folder1, folder2, ..]
    mapfile -t folders <<< "$folders"
else 
    folders=$1
fi

source_files=$(find "${folders[@]}" -type f \( -iname "*.cpp" -o -iname "*.hpp" \))

exit $(clang-format -sort-includes --dry-run --Werror ${source_files[@]})
