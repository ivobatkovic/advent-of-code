
cpp_files=$(find **/cpp/src/*.cpp)
hpp_files=$(find **/cpp/include/*.hpp)
for f in $cpp_files $hpp_files; do
    clang-format --style=google -sort-includes -i $f
done
exit $exit_code
