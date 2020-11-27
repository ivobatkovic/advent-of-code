import itertools,copy
import glob,os,sys
import time

sys.path.append(glob.glob(os.getcwd())[0] + "/../../day5/python")

from intcode import Intcode

def get_maximum_thrust(file_location):
  """ Goes through all permutations and checks the maximum thrust value. """

  max = -sys.maxsize
  for phase in itertools.permutations([0,1,2,3,4]):
    intcodes = [Intcode(file_location,[i],verbose=False) for i in phase]
    out = 0
    for intcode in intcodes:
      terminate,out = intcode(out)
      if out > max: max = out
  return max

def feedback_thrust(file_location):
  """ Goes through all permutations and returns the maximum feedback thrust. """

  max = -sys.maxsize

  for phase in itertools.permutations([5,6,7,8,9]):
    
    
    intcodes = [Intcode(file_location,[i],False,False) for i in phase]
    
    terminate,out = False,0
    
    while not terminate:
      for intcode in intcodes:
        terminate,out = intcode(out)
    if out > max:
      max = out
  return max

def main():

  file_location = "../data/input.csv"

  # Solve puzzle
  t0 = time.time()
  part_one = get_maximum_thrust(file_location)
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))

  t0 = time.time()
  part_two = feedback_thrust(file_location)
  time_part_two = round((time.time()-t0)*1e3)
  print("Solution to part two: %s (time taken %s[ms])" % (
      part_two, time_part_two))


if __name__=="__main__":
  main()
