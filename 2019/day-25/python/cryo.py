import sys,glob,os
sys.path.append(glob.glob(os.getcwd())[0] + "/../../day-5/python")
from intcode import Intcode


# Use different input method depending on python version
if sys.version_info.major == 3:
    def read_input(): return input()
else:
    def read_input(): return raw_input()

class Cryo:
  """ Class playing the game of navigating through the rooms """

  def __init__(aladeen,file):
    """ Initialize the intcode """
    aladeen.ic = Intcode(file = file, reset = False, verbose = False)

  def play(aladeen):
    """ Use the input from the terminal to play the game """
    message, row = [], ""
    while True:
      cond, output = aladeen.ic()

      # Run until we are promted an input
      if output is None:

        # Print current message
        for row in message:
          print(row)

        # Read user input
        aladeen.ic.input = [ord(i) for i in str(read_input()) + '\n']

        if (chr(aladeen.ic.input[0]) == 'q') or cond:
          return

        # Reset message
        message, row = [], ""

        # Wake the intcode computer
        aladeen.ic.idle = False

      # Otherwise build the screen
      else:
        # New line
        if output == 10:
          message.append(row)
          row = ""
        # Add to the row
        else:
          row += chr(output)



if __name__=="__main__":
  """ Play the final game of advent of code 2019 
      Solution to this input is to pick up:
      - klein bottle
      - mutex
      - hyper cube
      - mug """

  # Solve the final day by enjoying playing the game!
  cryo = Cryo('../input.csv')
  cryo.play()