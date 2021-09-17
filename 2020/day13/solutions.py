#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import math
import sys


sys.path.append(join(dirname(realpath(__file__)), *[".."]))


def transform_input(input_):
    # custom transform for the day
    inp = []
    for row in input_.splitlines():
        for digit in row.split(","):
            inp += [digit]
    return inp


def read_input(file_name="data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = f.read()

    return input_


def part1(input_):
    input_ = transform_input(input_)
    # First element is the time stamp
    timestamp = int(input_[0])

    #  Waiting time, and corresponding id
    wait = [1e12, 0]

    # Go through all ids
    for inp in input_[1:]:
        if inp == "x":
            continue
        # Id and departure time
        id = int(inp)
        dep_time = id * math.ceil(timestamp / id)

        # Check if departure time after time stamp and update minimum wait time
        if dep_time >= timestamp and (dep_time < wait[0]):
            wait = [dep_time, id]
    # Return wait time * id
    return (wait[0] - timestamp) * wait[1]


def part2(input_):
    input_ = transform_input(input_)
    # Get first digit (skip the timestamp)
    id = int(input_[1])

    # Starting time step, and cycle for reapeating
    i, cycle = 1, 1

    # Get the offset andstarting id
    for offset, next_id in enumerate(input_[2:], 1):
        if next_id == "x":
            continue
        # Check if we can find a multiple between id and next_id
        while True:
            # multiple * next_id + offset = id * j
            multiple = (i * id + offset) / int(next_id)

            # if multiple is a positive integer, we found a match
            if multiple % 1 == 0 and multiple > 0:
                break
            # Otherwise, keep going in cycle
            i += cycle
        # If we found a match, we need update the cycle of how frequently this
        # combination occurs
        cycle *= int(next_id)

    return i * id


def main():

    input_ = read_input()

    t0 = time.time()
    sol_part1 = part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {sol_part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    sol_part2 = part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {sol_part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize("input1, output1", [("data/test_input0.txt", 295)])
def test1(input1, output1):
    assert part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [
        ("data/test_input0.txt", 1068781),
        ("data/test_input1.txt", 3417),
        ("data/test_input2.txt", 754018),
        ("data/test_input3.txt", 779210),
        ("data/test_input4.txt", 1261476),
        ("data/test_input5.txt", 1202161486),
    ],
)
def test2(input2, output2):
    assert part2(read_input(input2)) == output2
