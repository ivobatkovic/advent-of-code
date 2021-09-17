from os.path import dirname
from os.path import realpath
from os.path import join
import sys
import time

sys.path.append(join(dirname(realpath(__file__)), *[".."]))

from day5.intcode import Intcode


def part1(input_):
    intcode = Intcode(input_, verbose=False, reset=True)
    _, part1 = intcode(1)
    return part1


def part2(input_):
    intcode = Intcode(input_, verbose=False, reset=True)
    _, part_two = intcode(5)
    return part_two


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


# def main():

#     dir_path = dirname(realpath(__file__))
#     file_location = join(dir_path, "../data/input.txt")

#     intcode = Intcode(file_location, verbose=False, reset=True)

#     t0 = time.time()
#     _, part_one = intcode(1)
#     time_part_one = round((time.time() - t0) * 1e3)
#     print(
#         "Solution to part one: %s (time taken %s[ms])"
#         % (part_one, time_part_one)
#     )

#     t0 = time.time()
#     _, part_two = intcode(5)
#     time_part_two = round((time.time() - t0) * 1e3)
#     print(
#         "Solution to part one: %s (time taken %s[ms])"
#         % (part_two, time_part_two)
#     )


if __name__ == "__main__":
    main()
