#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))


def transform_input(input_):
    # custom transform for the day
    return [int(inp) for inp in input_.splitlines()]


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_):

    # Keep track of loop sizes for the input
    loop_sizes = []
    # Go through each input
    for public_key in input_:
        # Start with zero loop size, and value 1
        loop_size, val = 0, 1
        while True:
            # If the handshake matches the public key, we found the loop size
            if val == public_key:
                break
            # Apply one loop_size transform
            val = (val * 7) % 20201227
            # Update number of loop sizes
            loop_size += 1
        # Store the found loop size
        loop_sizes.append(loop_size)

    # Extract the public key for either door/card
    subject_nr = input_[0]
    loop_size = loop_sizes[1]
    # Transform the subject number with the loop size
    val = 1
    for _ in range(loop_size):
        val = (val * subject_nr) % 20201227
    return val


def main():
    input_ = read_input()

    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize(
    "input1, output1", [("../data/test_input0.txt", 14897079)]
)
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1
