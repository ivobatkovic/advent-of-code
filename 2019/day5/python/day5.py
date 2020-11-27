from intcode import Intcode
import time
def main():

  intcode = Intcode("../data/input.csv",verbose=False,reset=True)

  t0 = time.time()
  _,part_one = intcode(1)
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))
  
  
  t0 = time.time()
  _,part_two = intcode(5)
  time_part_two = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_two, time_part_two))

if __name__ == "__main__":
  main()