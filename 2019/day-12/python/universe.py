from utils import Gravity

def gcd(a,b):
  """ Find greatest common divisor. """
  while b > 0:
    a, b = b, a % b
  return a

def lcm(a, b):
  """ Find least common multiple between a and b. """
  return a * b // gcd(a, b)


def main():

  # Solution one
  grav = Gravity('../input.txt')
  grav.update(1000)
  print("Solution to part one: " + str(grav.energy()))

  # Reset for solution tow
  grav = Gravity('../input.txt')
  print("Solution to part two: " + str(reduce(lcm,grav.cycles())))

if __name__=="__main__":
  main()
