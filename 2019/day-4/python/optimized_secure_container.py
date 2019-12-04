from utils import Digits
import time, copy
import numpy as np

def secure_container(input):
  """ Solves problem one and two by iterating over monotonic numbers and
  checking the double digits, with no adjacency, condition."""

  start = Digits.make_monotonic(np.array([int(char) for char in str(input[0])]))
  stop = np.array([int(char) for char in str(input[1])])

  sol1,sol2 = 0,0
  while(np.sum(start < stop)>0):
    sol1 = sol1+1 if Digits.double_digit(start) else sol1
    sol2 = sol2+1 if Digits.double_digit_no_adjacent(start) else sol2
    num = Digits.next_monotonic(start)

  return sol1,sol2

def main():
  """ Print out the problem solutions. """

  # Timing reference
  t0 = time.time()

  # Puzzle input
  input = [108457,562041]

  # Print solutions
  solution1,solution2 = secure_container(input)
  print("Solution to part one: " + str(solution1))
  print("Solution to part two: " + str(solution2))
  print("Run time " + str(time.time()-t0) + "s")

if __name__ == "__main__":
  main()
