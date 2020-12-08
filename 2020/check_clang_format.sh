exit_code=0

cpp_files=$(find **/cpp/src/*.cpp)
hpp_files=$(find **/cpp/include/*.hpp)
for f in $cpp_files $hpp_files; do
    output=$(clang-format --style=google -sort-includes -output-replacements-xml \
           $f | grep -c "<replacement ")
    if [ $output -ne "0" ]; then
        echo File $f needs reformatting
        exit_code=1
    fi
done
exit $exit_code
