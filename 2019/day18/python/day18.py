import time
from maze import Maze

if __name__ == "__main__":
  t0 = time.time()
  maze = Maze('../data/input.txt')
  part_one = maze.compute_shortest_path()
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))

  t0 = time.time()
  maze_ = Maze('../data/input.txt', True)
  part_two = maze_.compute_shortest_path()
  time_part_two = round((time.time()-t0)*1e3)
  print("Solution to part two: %s (time taken %s[ms])" % (
      part_two, time_part_two))