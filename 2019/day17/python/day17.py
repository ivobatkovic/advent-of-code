from asci import Asci
import time

def main(fileName):

  t0 = time.time()
  asci = Asci(fileName)
  part_one = asci.compute_intersections(True)
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))

  t0 = time.time()
  part_two = asci.collect_dust(True)
  time_part_two = round((time.time()-t0)*1e3)
  print("Solution to part two: %s (time taken %s[ms])" % (
      part_two, time_part_two))

if __name__ == "__main__":
  main('../data/input.csv')
