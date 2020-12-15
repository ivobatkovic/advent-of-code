from os.path import dirname
from os.path import realpath
from os.path import join
import itertools
import sys
import time

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))

from day5.python.intcode import Intcode


def get_maximum_thrust(file_location):
    """ Goes through all permutations and checks the maximum thrust value. """

    max = -sys.maxsize
    for phase in itertools.permutations([0, 1, 2, 3, 4]):
        intcodes = [Intcode(file_location, [i], verbose=False) for i in phase]
        out = 0
        for intcode in intcodes:
            terminate, out = intcode(out)
            if out > max:
                max = out
    return max


def feedback_thrust(file_location):
    """ Goes through permutations and returns the maximum feedback thrust. """

    max = -sys.maxsize

    for phase in itertools.permutations([5, 6, 7, 8, 9]):

        intcodes = [Intcode(file_location, [i], False, False) for i in phase]

        terminate, out = False, 0

        while not terminate:
            for intcode in intcodes:
                terminate, out = intcode(out)
        if out > max:
            max = out
    return max


def main():

    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")

    # Solve puzzle
    t0 = time.time()
    part_one = get_maximum_thrust(file_location)
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    t0 = time.time()
    part_two = feedback_thrust(file_location)
    time_part_two = round((time.time() - t0) * 1e3)
    print(
        "Solution to part two: %s (time taken %s[ms])"
        % (part_two, time_part_two)
    )


if __name__ == "__main__":
    main()
