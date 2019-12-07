import itertools,copy
import glob,os,sys

sys.path.append(glob.glob(os.getcwd())[0] + "/../../day-5/python")
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

  max,terminated = -sys.maxsize,False

  for phase in itertools.permutations([9,8,7,6,5]):
    intcodes = [Intcode(file_location,[i],False,False) for i in phase]
    terminate,out = False,0
    while not terminate:
      for intcode in intcodes:
        terminate,out = intcode(out)
    if out > max: max = out
  return max

def main():

  file_location = "../data.csv"

  part_one = str(get_maximum_thrust(file_location))
  print("Solution to part one: " + part_one)

  part_two = str(feedback_thrust("../data.csv"))
  print("Solution to part two: " + part_two)


if __name__=="__main__":
  main()
