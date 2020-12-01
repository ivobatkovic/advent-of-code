import time
from report import Report

if __name__ == "__main__":
  
  # Part one
  t0 = time.time()

  report = Report("../data/input.txt")
  part_one = report.part_one()
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % \
      (part_one, time_part_one))

  # Part two
  t0 = time.time()
  part_two = report.part_two()
  time_part_two = round((time.time()-t0)*1e3)
  print("Solution to part two: %s (time taken %s[ms])" % \
      (part_two, time_part_two))
  

