import itertools,copy
import glob,os,sys
import time
sys.path.append(glob.glob(os.getcwd())[0] + "/../../day-5/python")
from intcode import Intcode


def main():

  file_location = "../data.csv"

  ic = Intcode(file_location,verbose=False)
  _, part_one = ic(1)
  _, part_two = ic(2)
  print("Solution part one: " + str(part_one))
  print("Solution part one: " + str(part_two))



if __name__=="__main__":
  main()
