import glob,os,sys
import numpy as np
sys.path.append(glob.glob(os.getcwd())[0] + "/../../day-5/python")
from intcode import Intcode
from collections import defaultdict

def get_painted_tiles(map,intcode):
  """ Feeds input from the map (dict) to the intcode until it terminates.
  Returns the number of unique painted tiles."""

  px,py = 0,0
  dir = np.pi/2

  painted_tiles = {}

  terminated = False
  while not terminated:
    input = 0 if map[px,py] == '.' else 1

    cond1,paint = intcode(input)
    cond2,turn = intcode()

    dir = dir + np.pi/2 if turn == 0 else dir-np.pi/2
    color = "#" if paint==1 else "."

    if map[px,py] != color:
      painted_tiles[px,py] = 1
      map[px,py] = color

    py,px = py+int(np.cos(dir)), px-int(np.sin(dir))

    # Intcode terminated
    terminated = cond1 or cond2

  return len(painted_tiles),map

def print_map(map):
  """ Given the dict map, find [xmin,xmax] and [ymin,ymax] keys to print the
  painted registration. """

  x = [key[0] for key in map.keys()]
  y = [key[1] for key in map.keys()]

  for row in range(min(x),max(x)+1):
    msg = ["X" if map[row,j]=='#' else ' ' for j in range(min(y),max(y)+1)]
    print("".join(msg))

def main():

  # Part one
  map_part_one = defaultdict(lambda:'.')
  intcode_part_one = Intcode("../input.csv",verbose=False,reset=False)

  n_painted_tiles,_ = get_painted_tiles(map_part_one,intcode_part_one)
  print("Solution to part one: " + str(n_painted_tiles))

  # Part two
  map_part_two = defaultdict(lambda:'.'); map_part_two[0,0] = '#'
  intcode_part_two = Intcode("../input.csv",verbose=False,reset=False)

  _,map_part_two = get_painted_tiles(map_part_two,intcode_part_two)
  print("Solution to part two:"); print_map(map_part_two)

if __name__=="__main__":
  main()
