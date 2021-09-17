from os.path import dirname
from os.path import realpath
from os.path import join
import sys

sys.path.append(join(dirname(realpath(__file__)), *[".."]))
from day5.intcode import Intcode


class Beam:
    """Tractor beam class"""

    def __init__(self, fileName):
        """Initialize Beam with the intcode computer"""

        self.fileName = fileName
        self.ic = Intcode(fileName, verbose=False, reset=True)

    def part_one(self, grid_size=50):
        """Loop (x,y) in a N x N grid and sum up the output"""
        return sum(
            [
                self.ic([x, y])[1]
                for x in range(grid_size)
                for y in range(grid_size)
            ]
        )

    def part_two(self, square_size=100):
        """Move a square box of size NxN down and right until bottom
        left and top right corners both return output = 1"""
        # Bottom left X,Y coordinates
        bot_left = [0, square_size - 1]

        # Keep searching until we find the square box
        while True:

            # Check bottom left corner returns output 1
            if self.ic(bot_left)[1]:
                top_right = [
                    bot_left[0] + (square_size - 1),
                    bot_left[1] - (square_size - 1),
                ]
                # Check if also top right corner returns output 1
                if self.ic(top_right)[1]:
                    return bot_left[0] * 10000 + top_right[1]
                # Otherwise move down
                else:
                    bot_left[1] += 1

            # Otherwise move to the right
            else:
                bot_left[0] += 1
