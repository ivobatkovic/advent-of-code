file=$(find ./**/python/day*.py)
exit_code=0
for f in $file; do
  pytest $f
  if [ $? -eq 1 ]; then
    exit_code=1
  fi
done
echo Exit code $exit_code
exit $exit_code
