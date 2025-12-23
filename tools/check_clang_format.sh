#!/bin/bash

exit_code=0

# Append where to start looking from
if [ $# -eq 0 ]; then
    folders=$(git ls-files '*.cpp' '*.h' | awk -F/ '{print $1}' | sort -u)
else 
    folders=$1
fi

for folder in $folders; do
    source_files=$(find "$folder" -type f \( -iname "*.cpp" -o -iname "*.hpp" \))
    for f in $source_files; do
        output=$(clang-format -sort-includes -output-replacements-xml $f | grep -c "<replacement ")
        if [ $output -ne "0" ]; then
            echo File $f needs reformatting
            exit_code=1
        fi
    done
done
echo Done checking
exit $exit_code
