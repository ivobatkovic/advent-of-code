import math

def fuel_counter(masses):
  """ Function that computes the fuel needed for the input masses.
  Expected input is required to either be a list/tuple or scalar"""
  if isinstance(masses,(tuple,list)):
    return sum(fuel_counter(mass) for mass in masses)
  return max(int(math.floor(masses/3)-2),0)

def fuel_needed_total(mass):
  """ Function that computes the fuel needed for the mass and its own fuel.
  Expected input is a scalar """
  required_fuel = fuel_counter(mass)
  if required_fuel > 0:
    return required_fuel + fuel_needed_total(required_fuel)
  return 0

def fuel_counter_extended(masses):
  """ Function that computes the fuel needed for the input masses and the extra fuel needed for the new fuel itself.
  Expected input is required to either be a list/tuple or scalar"""
  if isinstance(masses,(tuple,list)):
    return sum(fuel_counter_extended(mass) for mass in masses)
  return fuel_needed_total(masses)

def main():
  # Open data file and read through all lines
  file_location = "../data.txt"
  try:
    with open(file_location) as f:
      masses = f.readlines()

    # Remove whitespace characters at end of each line
    masses = [int(x.strip()) for x in masses]

    # Print solutions
    print("Fuel needed for part one: " + str(fuel_counter(masses)))
    print("Fuel needed for part two: " + str(fuel_counter_extended(masses)))
  except IOError:
    print("Cannot find file at: " + file_location)

if __name__ == "__main__":
  main()
