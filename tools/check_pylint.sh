#!/bin/bash

exit_code=0

# Append where to start looking from
if [ $# -eq 0 ]; then
    folders=$(git ls-files '*.py' | awk -F/ '{print $1}' | sort -u)
    # Map string "folder1\nfolder2\n..." to an array [folder1, folder2, ..]
    mapfile -t folders <<< "$folders"
else 
    folders=$1
fi

if ! python3 -m flake8 "${folders[@]}" --count --select=E9,F63,F7,F82 --ignore=E203,402 --show-source --statistics; then
    exit_code=1
fi

if ! python3 -m flake8 "${folders[@]}" --count --max-complexity=10 --ignore=E203,E402,W503 --statistics;
then
    exit_code=1
fi

exit $exit_code
