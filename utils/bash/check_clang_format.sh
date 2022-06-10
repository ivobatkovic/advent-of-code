exit_code=0

# Append where to start looking from
if [ $# -eq 0 ]; then start="."
    else start=$1
fi
cpp_files=$(find $start -name '*.cpp')
hpp_files=$(find $start -name '*.hpp')
for f in $cpp_files $hpp_files; do
    output=$(clang-format --style=google -sort-includes -output-replacements-xml \
           $f | grep -c "<replacement ")
    if [ $output -ne "0" ]; then
        echo File $f needs reformatting
        exit_code=1
    fi
done
echo Done checking
exit $exit_code
