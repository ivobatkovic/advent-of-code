from planet import Planet
import time

if __name__ == "__main__":

  t0 = time.time()
  planet_one = Planet('../data/input.txt', recursive=False)
  part_one = planet_one.part_one()
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))

  t0 = time.time()
  planet_two = Planet('../data/input.txt', recursive=True)
  part_two = planet_two.part_two()
  time_part_two = round((time.time()-t0)*1e3)
  print("Solution to part two: %s (time taken %s[ms])" % (
      part_two, time_part_one))
