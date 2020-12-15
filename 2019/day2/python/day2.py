from os.path import dirname
from os.path import realpath
from os.path import join
import copy
import time


def intcode(x):
    """ Function that computes the intcode for the list x."""

    # Traverse x with a stride of 4
    for i in range(0, len(x), 4):
        # Kill the program
        if x[i] == 99:
            return x[0]
        # Addition
        elif x[i] == 1:
            x[x[i + 3]] = x[x[i + 1]] + x[x[i + 2]]
        # Multiplication
        elif x[i] == 2:
            x[x[i + 3]] = x[x[i + 1]] * x[x[i + 2]]

    # Reached the end
    return x[0]


def solve_intcode(x, x0, x1):
    """Function that takes input a list x and modifies it at positions
    x[1]=x0, x[2]=x1, and then computes the intcode of x."""

    # Make a copy
    x_copy = copy.deepcopy(x)

    # Modify
    x_copy[1], x_copy[2] = x0, x1
    return intcode(x_copy)


def solve_intcode_extended(x, output):
    """Function that takes input a list x and searches for value
    x[1],x[2] to get output from the intcode program."""
    for noun in range(0, 100):
        for verb in range(0, 100):
            if solve_intcode(x, noun, verb) == output:
                return 100 * noun + verb
    return 0


def main():
    # Open data file and read through all lines
    file_location = "../data/input.txt"
    try:
        dir_path = dirname(realpath(__file__))
        with open(join(dir_path, file_location), "r") as f:
            reader = f.read()

        # Map to list to int
        intcode_input = [int(r) for r in reader.split(",")]

        # Part one
        t0 = time.time()
        part_one = solve_intcode(intcode_input, 12, 2)
        time_part_one = round((time.time() - t0) * 1e3)
        print(
            "Solution to part one: %s (time taken %s[ms])"
            % (part_one, time_part_one)
        )

        t0 = time.time()
        part_two = solve_intcode_extended(intcode_input, 19690720)
        time_part_two = round((time.time() - t0) * 1e3)
        print(
            "Solution to part two: %s (time taken %s[ms])"
            % (part_two, time_part_two)
        )

    except IOError:
        print("Cannot find file at: " + file_location)


if __name__ == "__main__":
    main()
