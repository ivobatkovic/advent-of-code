from os.path import dirname
from os.path import realpath
from os.path import join
import sys
import numpy as np
import time

sys.path.append(join(dirname(realpath(__file__)), *[".."]))
from day8.utils import IO


class SpaceImage:
    """Class that reads Space images."""

    def __init__(self, input_, image_width, image_height):
        """Constructor: read image and specify dimensinons."""
        self.img = IO.read_image(input_, image_width, image_height)
        self.wide, self.tall = image_width, image_height

    def corruption_check(self):
        """Finds the layer in an image with fewest zeros and multiplies the number
        of 1 digits with number of 2 digits for that layer."""

        n_zero_layers = np.count_nonzero(self.img == 0, axis=(1, 2))
        layer = np.argmin(n_zero_layers)
        return np.sum(self.img[layer] == 1) * np.sum(self.img[layer] == 2)

    def reconstruct_image(self):
        """Decodes and prints the image."""

        out = 2 * np.ones((self.tall, self.wide))
        for img in self.img:
            mask = out == 2
            out[mask] = img[mask]

        # Printing each row
        for row in range(self.tall):
            print("".join(["X" if int(x) == 1 else " " for x in out[row, :]]))


def part1(input_):
    si = SpaceImage(input_, image_width=25, image_height=6)
    return si.corruption_check()


def part2(input_):
    si = SpaceImage(input_, image_width=25, image_height=6)
    si.corruption_check()
    return si.reconstruct_image()


def main():

    # Open data file and read through all lines
    file_location = "data/input.txt"
    try:
        dir_path = dirname(realpath(__file__))
        with open(join(dir_path, file_location), "r") as f:
            input_ = f.read()

        t0 = time.time()
        sol_part1 = part1(input_)
        time_end = round((time.time() - t0) * 1e3)

        print(
            "Solution to part one: %s (time taken %s[ms])"
            % (sol_part1, time_end)
        )

        t0 = time.time()
        sol_part2 = part2(input_)
        time_end = round((time.time() - t0) * 1e3)
        print(
            "Solution to part two: %s (time taken %s[ms])"
            % (sol_part2, time_end)
        )
    except IOError:
        print("Cannot find file at: " + file_location)


if __name__ == "__main__":
    main()
