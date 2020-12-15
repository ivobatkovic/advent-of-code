from os.path import dirname
from os.path import realpath
from os.path import join

from utils import Gravity
from functools import reduce
import time
import sys

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))


def gcd(a, b):
    """ Find greatest common divisor. """
    while b > 0:
        a, b = b, a % b
    return a


def lcm(a, b):
    """ Find least common multiple between a and b. """
    return a * b // gcd(a, b)


def main():

    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")

    # Solution one
    t0 = time.time()
    grav = Gravity(file_location)
    grav.update(1000)
    part_one = grav.energy()
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    t0 = time.time()
    grav = Gravity(file_location)
    part_two = reduce(lcm, grav.cycles())
    time_part_two = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_two, time_part_two)
    )


if __name__ == "__main__":
    main()
