from os.path import dirname
from os.path import realpath
from os.path import join
import sys

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))
from day5.python.intcode import Intcode


class Cryo:
    """Class playing the game of navigating through the rooms"""

    def __init__(self, file):
        """Initialize the intcode"""
        self.ic = Intcode(file=file, reset=False, verbose=False)

    def play(self):
        """Use the input from the terminal to play the game"""
        message, row = [], ""
        while True:
            cond, output = self.ic()

            # Run until we are promted an input
            if output is None:

                # Print current message
                for row in message:
                    print(row)

                # Read user input
                self.ic.input = [ord(i) for i in str(input()) + "\n"]

                if (chr(self.ic.input[0]) == "q") or cond:
                    return

                # Reset message
                message, row = [], ""

                # Wake the intcode computer
                self.ic.idle = False

            # Otherwise build the screen
            else:
                # New line
                if output == 10:
                    message.append(row)
                    row = ""
                # Add to the row
                else:
                    row += chr(output)
