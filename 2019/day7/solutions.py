from os.path import dirname
from os.path import realpath
from os.path import join
import itertools
import sys
import time

sys.path.append(join(dirname(realpath(__file__)), *[".."]))
from day5.intcode import Intcode


def part1(input_):
    """Goes through all permutations and checks the maximum thrust value."""

    max = -sys.maxsize
    for phase in itertools.permutations([0, 1, 2, 3, 4]):
        intcodes = [Intcode(input_, [i], verbose=False) for i in phase]
        out = 0
        for intcode in intcodes:
            terminate, out = intcode(out)
            if out > max:
                max = out
    return max


def part2(input_):
    """Goes through permutations and returns the maximum feedback thrust."""

    max = -sys.maxsize

    for phase in itertools.permutations([5, 6, 7, 8, 9]):

        intcodes = [Intcode(input_, [i], False, False) for i in phase]

        terminate, out = False, 0

        while not terminate:
            for intcode in intcodes:
                terminate, out = intcode(out)
        if out > max:
            max = out
    return max


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
