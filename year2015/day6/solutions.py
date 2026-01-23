#!/usr/bin/env python3
import argparse
import numpy as np
import re
import pytest
import time


def transform_input(input_):

    numbers_regex = re.compile(r"\d+")
    action_regex = re.compile("(on|off|toggle)")

    output = []
    for line in input_.splitlines():
        action = action_regex.search(line).group(0)
        numbers = tuple(map(int, numbers_regex.findall(line)))
        output.append((action, numbers))
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    grid = np.zeros((1000, 1000), dtype=int)

    for action, (x0, y0, x1, y1) in inp:

        slice_ = grid[x0 : x1 + 1, y0 : y1 + 1]

        if action == "on":
            slice_[:] = 1
        elif action == "off":
            slice_[:] = 0
        else:
            slice_[:] = 1 - slice_

    return np.sum(grid)


def solve_part2(input_):
    inp = transform_input(input_)

    grid = np.zeros((1000, 1000), dtype=int)

    for action, (x0, y0, x1, y1) in inp:
        slice_ = grid[x0 : x1 + 1, y0 : y1 + 1]

        if action == "on":
            slice_[:] += 1
        elif action == "off":
            slice_[:] = np.maximum(slice_[:] - 1, 0)
        else:
            slice_[:] += 2

    return np.sum(grid)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2015 day 6")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2015/day6/data/input.txt",
        nargs="?",
        help="Path to data file",
    )
    return parser.parse_args()


def main():
    parser = parse_args()
    input_ = read_input(parser.file_name)

    t0 = time.time()
    part1 = solve_part1(input_)
    time_part1 = round((time.time() - t0) * 1e3)
    print(f"Solution to part one: {part1} (time taken {time_part1:.2f}[ms])")

    t0 = time.time()
    part2 = solve_part2(input_)
    time_part2 = round((time.time() - t0) * 1e3)
    print(f"Solution to part two: {part2} (time taken {time_part2:.2f}[ms])")


if __name__ == "__main__":
    main()


@pytest.mark.parametrize(
    "input1, output1", [("year2015/day6/data/test_input0.txt", 998996)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2015/day6/data/test_input1.txt", 2000001)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
