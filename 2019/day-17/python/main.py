from asci import Asci

def main(fileName = '../input.csv'):

  asci = Asci(fileName)
  print_map = True
  print("Solution to part one: %s" % asci.compute_intersections(print_map))

  print_iterations = True
  print("Solution to part one: %s" % asci.collect_dust(print_iterations))

if __name__ == "__main__":
  main('../input.csv')
