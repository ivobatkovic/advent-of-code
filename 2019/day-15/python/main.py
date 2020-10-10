from droid import Droid

def main():

  droid = Droid("../input.csv")

  map,output = droid.repair_oxygen()
  print("Solution to part one: %s" % output[-1])

  max_depth = droid.fill_oxygen(map,output[0],output[1])
  print("Solution to part two: %s" % max_depth)

if __name__=="__main__":
  main()
