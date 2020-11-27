import itertools,copy
import glob,os,sys
import time
sys.path.append(glob.glob(os.getcwd())[0] + "/../../day5/python")
from intcode import Intcode

def main():

  file_location = "../data/input.csv"

  ic = Intcode(file_location,verbose=False)
  
  # Solve puzzle
  t0 = time.time()
  _,part_one = ic(1)
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))

  t0 = time.time()
  _,part_two = ic(2)
  time_part_two = round((time.time()-t0)*1e3)
  print("Solution to part two: %s (time taken %s[ms])" % (
      part_two, time_part_two))


if __name__=="__main__":
  main()
