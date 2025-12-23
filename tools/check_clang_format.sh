#!/bin/bash

exit_code=0

# Append where to start looking from
if [ $# -eq 0 ]; then start="."
    else start=$1
fi
source_files=$(find $start -type f \( -iname \*.cpp -o -iname \*.c \))
header_files=$(find $start -type f \( -iname \*.hpp -o -iname \*.h \))
for f in $source_files $header_files; do
    output=$(clang-format -sort-includes -output-replacements-xml \
           $f | grep -c "<replacement ")
    if [ $output -ne "0" ]; then
        echo File $f needs reformatting
        exit_code=1
    fi
done
echo Done checking
exit $exit_code
