#!/usr/bin/env python3
import argparse
import re
import pytest
import time

from collections import defaultdict

neighbors = [
    (-1, -1),
    (-1, 0),
    (-1, 1),
    (0, -1),
    (0, 1),
    (1, -1),
    (1, 0),
    (1, 1),
]


def transform_input(input_):

    numbers = defaultdict(list)
    symbols = {}

    regex_digits = re.compile(r"\d+")
    regex_non_digits = re.compile(r"[^\d|^\.]")

    for i, line in enumerate(input_.splitlines()):

        # Look for numbers on the line
        for start_match, match in [
            (m.start(), m.group()) for m in regex_digits.finditer(line)
        ]:
            positions = [
                (i, j) for j in range(start_match, start_match + len(match))
            ]
            numbers[int(match)].append(positions)

        # Look for symbols on the line
        for pos, match in [
            (m.start(), m.group()) for m in regex_non_digits.finditer(line)
        ]:
            symbols[(i, pos)] = match
    return numbers, symbols


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def are_positions_adjacent(positions, symbols):
    for pos in positions:
        for dx, dy in neighbors:
            if (pos[0] + dx, pos[1] + dy) in symbols:
                return True
    return False


def solve_part1(input_):
    numbers, symbols = transform_input(input_)

    return sum(
        [
            key
            for key, values in numbers.items()
            for positions in values
            if are_positions_adjacent(positions, symbols)
        ]
    )


def invert_map(numbers):

    output = {}
    for key, values in numbers.items():
        for sub_values in values:
            for pos in sub_values:
                output[pos] = key
    return output


def get_gear_ratio(pos, numbers):

    visited = set()

    for dx, dy in neighbors:
        new_pos = pos[0] + dx, pos[1] + dy
        if new_pos in numbers:
            visited.add(numbers[new_pos])

    if len(visited) == 2:
        return visited.pop() * visited.pop()
    return 0


def solve_part2(input_):
    numbers, symbols = transform_input(input_)

    inverted_numbers = invert_map(numbers)

    return sum(
        [
            get_gear_ratio(key, inverted_numbers)
            for key, value in symbols.items()
            if value == "*"
        ]
    )


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2023 day 3")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2023/day3/data/input.txt",
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
    "input1, output1", [("year2023/day3/data/test_input0.txt", 4361)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2023/day3/data/test_input0.txt", 467835)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
