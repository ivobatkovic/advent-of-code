#!/usr/bin/env python3
from os.path import dirname
from os.path import realpath
from os.path import join
import time
import pytest
import sys

sys.path.append(join(dirname(realpath(__file__)), *[".."]))


def transform_input(input_):
    # custom transform for the day
    return [int(inp) for inp in input_.splitlines()]


def read_input(file_name="data/input.txt"):
    dir_path = dirname(realpath(__file__))
    with open(join(dir_path, file_name), "r") as f:
        input_ = f.read()

    return input_


def sort_input(input_):
    data = sorted(input_)
    return [0] + data + [data[-1] + 3]


def part1(input_):

    data = sort_input(transform_input(input_))

    diff1, diff3 = 0, 0
    # Go through the sorted chain of adapters and check difference
    for i in range(len(data) - 1):
        diff = data[i + 1] - data[i]
        if diff == 3:
            diff3 += 1
        elif diff == 1:
            diff1 += 1
    return diff1 * diff3


def part2(input_):

    data = sort_input(transform_input(input_))

    # Keep track of number of combinations to reach the last adapter.
    # We add 1 to the last adapter since it can only be combined in one way!
    d = [0] * (len(data) - 1) + [1]

    # We look back in the adaptor chain with these steps to see if we can
    # connect adapter at index i-steps with index i
    steps = [1, 2, 3]

    # Go through the sorted input list in reverse
    for i in range(len(data) - 1, 0, -1):
        for step in steps:
            # Look if we can connect adapter at i-step to adapter at i
            if i - step > -1 and data[i] - data[i - step] <= 3:
                d[i - step] += d[i]

    # d[0] contains number of possible combinations to go from the first to
    # last adapter.
    return d[0]


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


@pytest.mark.parametrize("input1, output1", [("data/test_input0.txt", 35)])
def test1(input1, output1):
    assert part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [("data/test_input0.txt", 8), ("data/test_input1.txt", 19208)],
)
def test2(input2, output2):
    assert part2(read_input(input2)) == output2
