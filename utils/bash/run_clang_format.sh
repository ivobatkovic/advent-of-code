# Append where to start looking from
if [ $# -eq 0 ]; then start="."
    else start=$1
fi
cpp_files=$(find $start -name '*.cpp')
hpp_files=$(find $start -name '*.hpp')
for f in $cpp_files $hpp_files; do
    clang-format --style=google -sort-includes -i $f
done
echo Done formatting
