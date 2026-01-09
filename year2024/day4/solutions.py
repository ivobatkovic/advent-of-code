#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    output = {}

    for i, line in enumerate(input_.splitlines()):
        for j, char in enumerate(line):
            output[(i, j)] = char
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)

    directions = [
        (1, 0),
        (1, 1),
        (0, 1),
        (-1, 1),
        (-1, 0),
        (-1, -1),
        (0, -1),
        (1, -1),
    ]

    output = 0
    for (x, y), value in inp.items():
        if value != "X":
            continue

        # Check all directions for remaining MAS
        for dx, dy in directions:
            match = ""
            for k in range(1, 4):
                match += (
                    inp[(x + k * dx, y + k * dy)]
                    if (x + k * dx, y + k * dy) in inp
                    else ""
                )

            if match == "MAS":
                output += 1

    return output


def solve_part2(input_):
    inp = transform_input(input_)
    output = 0

    # Check only diagonals for the X shape
    directions = [(1, 1), (-1, 1), (-1, -1), (1, -1)]

    center_pos = []
    for (x, y), value in inp.items():
        if value != "M":
            continue

        # Check all diagonal directions for remaining AS
        for dx, dy in directions:
            match = ""
            for k in range(1, 3):
                match += (
                    inp[(x + k * dx, y + k * dy)]
                    if (x + k * dx, y + k * dy) in inp
                    else ""
                )

            if match == "AS":
                center_pos.append((x + dx, y + dy))

    # Overlapping center positions form an X
    for i in range(len(center_pos) - 1):
        for j in range(i + 1, len(center_pos)):
            if center_pos[i] == center_pos[j]:
                output += 1

    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2024 day 4")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2024/day4/data/input.txt",
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
    "input1, output1", [("year2024/day4/data/test_input0.txt", 18)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2024/day4/data/test_input0.txt", 9)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
