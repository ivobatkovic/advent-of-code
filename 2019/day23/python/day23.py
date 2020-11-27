from network import Network
import time


if __name__ == "__main__":

  t0 = time.time()
  file = '../data/input.txt'
  network = Network('../data/input.csv')
  part_one, part_two = network.run()
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))

  time_part_two = round((time.time()-t0)*1e3)
  print("Solution to part two: %s (time taken %s[ms])" % (
      part_two, time_part_one))
