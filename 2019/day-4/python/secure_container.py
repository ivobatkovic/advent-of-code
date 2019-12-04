def double_digit(num):
  """ Checks if there exist two adjacent matching digits. """

  for i in range(0,len(num)-1):
    if num[i] == num[i+1]:
      return True
  return False

def double_digit_no_adjacent(num):
  """ Checks if there exist two adjacent matching digits that are not part of as
  larger group of matching digits."""

  for i in range(0,len(num)-1):
    if num[i] == num[i+1]:
      # Special case in the beginning of the number
      if i==0 and num[i+1] != num[i+2]:
        return True
      # Special case in the end of the number
      if i==len(num)-2 and num[i-1] != num[i]:
        return True
      # Somwhere in the middle of the number
      elif num[i-1] != num[i] and num[i+1] != num[i+2]:
        return True
  return False

def monotonic(num):
  """ Checks if the string changes after sorting it. If it does, the number
  is not monotonic."""

  return num == "".join(sorted(num))

def verify_part_one(num):
  """ Returns the monotonic and double digit conditions for part one."""

  return monotonic(num) and double_digit(num)

def verify_part_two(num):
  """ Returns the monotonic and double digit conditions for part two."""

  return monotonic(num) and double_digit_no_adjacent(num)

def secure_container(input):
  """ Computes the 'Secure Container' for the given input. """

  return sum([verify_part_one(str(i)) for i in range(input[0],input[1]+1)]), \
         sum([verify_part_two(str(i)) for i in range(input[0],input[1]+1)])

def main():

  # Solve puzzle
  part_one, part_two = secure_container([108457,562041])

  # Print solutions
  print("Solution to part one: " + str(part_one))
  print("Solution to part two: " + str(part_two))

if __name__ == "__main__":
  main()
