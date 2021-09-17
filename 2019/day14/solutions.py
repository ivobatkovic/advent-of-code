from os.path import dirname
from os.path import realpath
from os.path import join
import math

import time
import sys

sys.path.append(join(dirname(realpath(__file__)), *[".."]))
from day14.utils import IO


# Compute how many of the <key> needed to create fuel
def compute(formula, key, amount=1):
    """Function that computes the amount of fuel needed to create the
    component KEY. Uses the formula input to follow the process chain."""

    # If you reach FUEL, just return how much <fuel> you need
    if key == "FUEL":
        return amount

    # Count how many <key> componenets needed for <amount> FUEL
    s = 0
    for form in formula[key]:
        # Compute how many sub-components you need for <amount> of FUEL
        total = compute(formula, form[-1], amount)

        # Round up the conversion process to the closest integer
        s += int(math.ceil(total / float(form[1])) * form[0])
    return int(s)


def compute_fuel(formula, ore=int(1e12)):
    """Function to compute maximum fuel, given number of OREs.
    Uses binary tree search to find the correct value."""

    # Start with interval [1,ore]
    fuel_min, fuel_max = 1, ore

    # If fuel_max = fuel_min; break
    while (fuel_max - fuel_min) > 1:
        mid = (fuel_min + fuel_max) // 2

        # Update lower bound since we dont exceed our ORE amount.
        if compute(formula, "ORE", mid) <= ore:
            fuel_min = mid
        else:
            fuel_max = mid
    return fuel_min


def part1(input_):
    formula = IO.readFile(input_)
    return compute(formula, "ORE", 1)


def part2(input_):
    formula = IO.readFile(input_)
    return compute_fuel(formula)


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
