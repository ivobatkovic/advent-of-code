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
    return [int(inp) for inp in input_.split(",")]


def read_input(file_name="../data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = transform_input(f.read())

    return input_


def solve_part1(input_, end_dig=2020):

    dig_spoken = [0] * end_dig
    for i, dig in enumerate(input_[:-1]):
        dig_spoken[dig] = i + 1
    prev_dig = input_[-1]

    for i in range(len(input_), end_dig):

        if dig_spoken[prev_dig] == 0:
            dig_spoken[prev_dig] = i
            prev_dig = 0
        else:
            diff = i - dig_spoken[prev_dig]
            dig_spoken[prev_dig] = i
            prev_dig = diff

    return prev_dig


def solve_part2(input_):
    return solve_part1(input_, end_dig=30000000)


def main():
    input_ = read_input()

    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part two: {part2} (time taken {time_part2}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize(
    "input1, output1",
    [
        ("../data/test_input0.txt", 436),
        ("../data/test_input1.txt", 1),
        ("../data/test_input2.txt", 10),
        ("../data/test_input3.txt", 27),
        ("../data/test_input4.txt", 78),
        ("../data/test_input5.txt", 438),
        ("../data/test_input6.txt", 1836),
    ],
)
def test1(input1, output1):
    assert solve_part1(read_input(input1)) == output1
