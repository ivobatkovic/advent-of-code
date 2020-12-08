file="$(find **/python/day*.py)"
exit_code=0
for f in $file; do
  pytest $f
  if [[ $? -eq 1 ]]; then
    exit_code=1
  fi
done
exit $exit_code