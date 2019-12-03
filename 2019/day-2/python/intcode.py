import csv
import copy

def intcode(x):
  """ Function that computes the intcode for the list x."""

  # Traverse x with a stride of 4
  for i in xrange(0,len(x),4):
    # Kill the program
    if (x[i] == 99):
      return x[0]
    # Addition
    elif x[i] == 1:
      x[x[i+3]] = x[x[i+1]]+x[x[i+2]]
    # Multiplication
    elif x[i] == 2:
      x[x[i+3]] = x[x[i+1]]*x[x[i+2]]

  # Reached the end
  return x[0]

def solve_intcode(x,x0,x1):
  """ Function that takes input a list x and modifies it at positions
  x[1]=x0, x[2]=x1, and then computes the intcode of x."""

  # Make a copy
  x_copy = copy.deepcopy(x)

  # Modify
  x_copy[1], x_copy[2] = x0,x1
  return intcode(x_copy)


def solve_intcode_extended(x,output):
  """ Function that takes input a list x and searches for value
  x[1],x[2] to get output from the intcode program."""
  for noun in range(0,100):
    for verb in range(0,100):
      if(solve_intcode(x,noun,verb)==output):
        print(noun,verb)
        return 100*noun+verb
  return 0


def main():
  # Open data file and read through all lines
  file_location = "../data.csv"
  try:
    with open(file_location) as csvfile:
      reader = csv.reader(csvfile,delimiter=',')

      # Go through each row of the csv
      for row in reader:

        # Map to list to int
        intcode_input = map(int,row)
        print(intcode_input)
        print("Solution to part one: " +
          str(solve_intcode(intcode_input,12,2)))

        print("Solution to part two: " +
          str(solve_intcode_extended(intcode_input,19690720)))
    csvfile.close()

  except IOError:
    print("Cannot find file at: " + file_location)

if __name__ == "__main__":
  main()
