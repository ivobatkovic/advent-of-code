import numpy as  np

def fuel_counter(masses):
  """ Function that computes the fuel needed for the input masses.
  Expected input is required to either be a list/tuple or scalar"""
  if isinstance(masses,(tuple,list)):
    return int(sum(round(mass/3)-2 for mass in masses))
  return int(round(masses/3)-2)

def main():
  # Open data file and read through all lines
  filepath = "../data.txt"

  try:
    with open(filepath) as f:
      masses = f.readlines()
    # Remove whitespace characters at end of each line
    masses = [int(x.strip()) for x in masses] 
    
    print(fuel_counter(masses))
  except:
    print("Cannot file at: " + filepath)
  
if __name__ == "__main__":
  main()



