from beam import Beam
import  time

if __name__ == "__main__":

  t0 = time.time()
  beam = Beam('../data/input.csv')
  part_one = beam.part_one()
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))

  t0 = time.time()
  part_two = beam.part_two()
  time_part_two = round((time.time()-t0)*1e3)
  print("Solution to part two: %s (time taken %s[ms])" % (
      part_two, time_part_two))