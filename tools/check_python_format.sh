#!/bin/bash

# Append where to start looking from
if [ $# -eq 0 ]; then
    folders=$(git ls-files '*.py' | awk -F/ '{print $1}' | sort -u)
    # Map string "folder1\nfolder2\n..." to an array [folder1, folder2, ..]
    mapfile -t folders <<< "$folders"
else 
    folders=$1
fi

if ! python3 -m black ${folders[@]} --check --line-length 79; then
    exit 1
fi

exit 0
