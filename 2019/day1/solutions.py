from os.path import dirname
from os.path import realpath
from os.path import join
import math
import time


def transform_input(input_):
    # Remove whitespace characters at end of each line
    return [int(x.strip()) for x in input_.splitlines()]


def fuel_counter(masses):
    """Function that computes the fuel needed for the input masses.
    Expected input is required to either be a list/tuple or scalar"""
    if isinstance(masses, (tuple, list)):
        return sum(fuel_counter(mass) for mass in masses)
    return max(int(math.floor(masses / 3) - 2), 0)


def fuel_needed_total(mass):
    """Function that computes the fuel needed for the mass and its own fuel.
    Expected input is a scalar"""
    required_fuel = fuel_counter(mass)
    if required_fuel > 0:
        return required_fuel + fuel_needed_total(required_fuel)
    return 0


def fuel_counter_extended(masses):
    """Function that computes the fuel needed for the input masses and the extra
    fuel needed for the new fuel itself. Input is required to either be a
    list/tuple or scalar"""
    if isinstance(masses, (tuple, list)):
        return sum(fuel_counter_extended(mass) for mass in masses)
    return fuel_needed_total(masses)


def part1(input_):
    return fuel_counter(transform_input(input_))


def part2(input_):
    return fuel_counter_extended(transform_input(input_))


def main():
    # Open data file and read through all lines
    file_location = "data/input.txt"
    try:
        dir_path = dirname(realpath(__file__))
        with open(join(dir_path, file_location), "r") as f:
            masses = f.read()

        # Part one
        t0 = time.time()
        part_one = part1(masses)
        time_part_one = round((time.time() - t0) * 1e3)
        print(
            "Solution to part one: %s (time taken %s[ms])"
            % (part_one, time_part_one)
        )

        t0 = time.time()
        part_two = part2(masses)
        time_part_two = round((time.time() - t0) * 1e3)
        print(
            "Solution to part two: %s (time taken %s[ms])"
            % (part_two, time_part_two)
        )

    except IOError:
        print("Cannot find file at: " + file_location)


if __name__ == "__main__":
    main()
