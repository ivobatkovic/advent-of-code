from utils import Digits
import time

def verify_part_one(num):
  """ Returns the monotonic and double digit conditions for part one."""

  return Digits.monotonic(num) and Digits.double_digit(num)

def verify_part_two(num):
  """ Returns the monotonic and double digit conditions for part two."""

  return Digits.monotonic(num) and Digits.double_digit_no_adjacent(num)

def secure_container(input):
  """ Computes the solution for the given input. """

  return sum([verify_part_one(str(i)) for i in range(input[0],input[1]+1)]), \
         sum([verify_part_two(str(i)) for i in range(input[0],input[1]+1)])

def main():
  """ Print out the problem solutions. """

  # Timing reference
  t0 = time.time()

  # Puzzle input
  input = [108457,562041]

  # Solve puzzle
  part_one, part_two = secure_container([108457,562041])

  # Print solutions
  print("Solution to part one: " + str(part_one))
  print("Solution to part two: " + str(part_two))
  print("Run time " + str(time.time()-t0) + "s")

if __name__ == "__main__":
  main()
