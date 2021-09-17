from os.path import dirname
from os.path import realpath
from os.path import join
import time
import sys
import numpy as np

sys.path.append(join(dirname(realpath(__file__)), *[".."]))
from day4.utils import Digits


def transform_input(input_):
    return input_.split("-")


def part1(input_):

    input_ = transform_input(input_)
    start = Digits.make_monotonic(
        np.array([int(char) for char in str(input_[0])])
    )
    stop = np.array([int(char) for char in str(input_[1])])

    sol1 = 0
    while np.sum(start < stop) > 0:
        sol1 += 1 if Digits.double_digit(start) else 0
        start = Digits.next_monotonic(start)

    return sol1


def part2(input_):
    input_ = transform_input(input_)
    start = Digits.make_monotonic(
        np.array([int(char) for char in str(input_[0])])
    )
    stop = np.array([int(char) for char in str(input_[1])])

    sol2 = 0
    while np.sum(start < stop) > 0:
        sol2 += 1 if Digits.double_digit_no_adjacent(start) else 0
        start = Digits.next_monotonic(start)
    return sol2


def main():
    """Print out the problem solutions."""

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
