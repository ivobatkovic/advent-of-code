import sys,glob,os
sys.path.append(glob.glob(os.getcwd())[0] + "/../../day5/python")
from intcode import Intcode

class Springdroid:
  """ Class for the springdroid """

  def __init__(self,file):
    """ Assign filename """
    self.file = file

  def part_one(self):
    """ Solve part one by writing the program """

    program = ["NOT B T\n","AND D T\n","OR T J\n", "NOT C T\n","AND D T\n",\
               "OR T J\n","NOT A T\n","OR T J\n", "WALK\n"]

    return self.solve_program(program)

  def part_two(self):
    """ Solve part one by writing the program """

    program = ["NOT B T\n", "AND D T\n", "OR T J\n", "NOT C T\n", "AND D T\n", \
               "AND H T\n","OR T J\n", "NOT A T\n", "OR T J\n", "RUN\n"]

    return self.solve_program(program)

  def solve_program(self,program):
    """ Uses the program to run the springdroid """

    # Go through the program and pass it on to the intcode computer
    input = [ord(asci) for letter in program for asci in letter]
    intcode = Intcode(self.file, input = input, verbose = False, reset = False)

    message, row_message = [], ""
    while True:

      # Get output from intcode
      cond, out = intcode()

      # If we reached a stop point, print out where we failed
      if cond:
        for row in message: print(row)
        return "Failed"
      # If not an asci number, we reached the goal
      elif out > 255:
        return out
      # If not a new line append
      if out != 10:
        row_message += chr(out)
      # Append the row to the message
      else:
        message.append(row_message)
        row_message = ""
