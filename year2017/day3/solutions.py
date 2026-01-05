#!/usr/bin/env python3
import argparse
import pytest
import time

from collections import defaultdict


def transform_input(input_):
    return [int(x) for x in input_.splitlines()]


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def find_layer_and_start_value(digit):
    """Find which layer the digit belongs to and the layer's starting value."""

    layer = 0
    value = 1

    while True:
        # Number of digits per layer
        N = 1 + 2 * layer
        if digit > value + 1 and digit < value + 4 * N - 4:
            return value + 1, layer
        value += 4 * N - 4
        layer += 1


def get_manhattan_distance(digit):
    """Find the Manhattan Distance for the digit."""

    if digit == 1:
        return 0

    value, layer = find_layer_and_start_value(digit)

    start_pos = (layer, 1 - layer)
    diff = digit - value

    # Number of elements in the layer
    N = 1 + 2 * layer

    # Traverse along the right side
    if diff <= N - 2:
        pos = start_pos[0], start_pos[1] + diff
    # Traverse along the top side
    elif diff <= 2 * N - 3:
        diff -= N - 2
        pos = start_pos[0] - diff, start_pos[1] + N - 2
    # Traverse along the left side
    elif diff < 3 * N - 4:
        diff -= 2 * N - 3
        pos = start_pos[0] - (N - 1), start_pos[1] + N - 2 - diff
    # Traverse along the bottom side
    else:
        diff -= 3 * N - 4
        pos = start_pos[0] - (N - 1) + diff, start_pos[1] - 1
    return abs(pos[1]) + abs(pos[0])


def solve_part1(input_):
    inp = transform_input(input_)

    return sum([get_manhattan_distance(digit) for digit in inp])


def find_value(digit):
    """Traverse the grid until a value greater than digit is found."""

    neighbors = [
        (-1, 0),
        (-1, -1),
        (-1, 1),
        (0, 1),
        (0, -1),
        (1, 1),
        (1, 0),
        (1, -1),
    ]

    table = defaultdict(int, {(0, 0): 1})

    pos = (1, 0)
    layer = 1
    while True:
        N = 1 + 2 * layer

        # Loop over the elements of each layer in the spiral
        for k in range(1, 4 * N - 4 + 1):
            val = sum(
                [table[(pos[0] + dx, pos[1] + dy)] for dx, dy in neighbors]
            )
            table[pos] = val

            if val > digit:
                return val

            # Right side
            if k <= N - 2:
                pos = pos[0], pos[1] + 1
            # Top side
            elif k <= 2 * N - 3:
                pos = pos[0] - 1, pos[1]
            # Left side
            elif k <= 3 * N - 4:
                pos = pos[0], pos[1] - 1
            # Bottom
            else:
                pos = pos[0] + 1, pos[1]
        # Increase the layer of the spiral
        layer += 1


def solve_part2(input_):
    inp = transform_input(input_)

    return sum([find_value(digit) for digit in inp])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2017 day 3")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2017/day3/data/input.txt",
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
    "input1, output1", [("year2017/day3/data/test_input0.txt", 0 + 3 + 2 + 31)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2017/day3/data/test_input1.txt", 11 + 26 + 747)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
