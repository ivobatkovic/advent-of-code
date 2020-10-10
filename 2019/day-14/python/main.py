import math
from utils import IO

# Compute how many of the <key> needed to create fuel
def compute(formula,key,amount=1):
  ''' Function that computes the amount of fuel needed to create the
  component KEY. Uses the formula input to follow the process chain.'''

  # If you reach FUEL, just return how much <fuel> you need
  if key == 'FUEL':
    return amount

  # Count how many <key> componenets needed for <amount> FUEL
  s=0
  for form in formula[key]:
    # Compute how many sub-components you need for <amount> of FUEL
    total = compute(formula,form[-1],amount)

    # Round up the conversion process to the closest integer
    s += int(math.ceil(total/float(form[1]))*form[0])
  return int(s)

def compute_fuel(formula,ore = int(1e12)):
  ''' Function to compute maximum fuel, given number of OREs.
  Uses binary tree search to find the correct value.'''

  # Start with interval [1,ore]
  fuel_min, fuel_max = 1, ore

  # If fuel_max = fuel_min; break
  while (fuel_max - fuel_min) > 1:
    mid = (fuel_min + fuel_max) // 2

    # Update lower bound since we dont exceed our ORE amount.
    if compute(formula,'ORE',mid) <= ore:
      fuel_min = mid
    else:
      fuel_max = mid
  return fuel_min


def main():
  # Get dependency formula
  formula = IO.readFile("../input.txt")

  print("Solution to part one: %s" % compute(formula,'ORE',1))
  print("Solution to part two: %s" % compute_fuel(formula))

if __name__=="__main__":
  main()
