from springdroid import Springdroid
import time
if __name__ == '__main__':

  t0 = time.time()
  droid = Springdroid('../data/input.csv')
  part_one = droid.part_one()
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))

  t0 = time.time()
  part_two = droid.part_two()
  time_part_two = round((time.time()-t0)*1e3)
  print("Solution to part two: %s (time taken %s[ms])" % (
      part_two, time_part_two))