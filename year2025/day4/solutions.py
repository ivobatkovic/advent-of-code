#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    output = set()
    for i, line in enumerate(input_.splitlines()):
        for j, char in enumerate(line):
            if char == "@":
                output.add((i, j))
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


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


def solve_part1(input_):
    inp = transform_input(input_)

    output = 0
    for key in inp:
        tot_neighbors = sum(
            [1 for dx, dy in neighbors if (key[0] + dx, key[1] + dy) in inp]
        )

        if tot_neighbors < 4:
            output += 1
    return output


def solve_part2(input_):
    inp = transform_input(input_)

    output = 0

    while True:
        keys_to_remove = []
        for key in inp:
            tot_neighbors = sum(
                [
                    1
                    for dx, dy in neighbors
                    if (key[0] + dx, key[1] + dy) in inp
                ]
            )

            if tot_neighbors < 4:
                keys_to_remove.append(key)
                output += 1

        if not keys_to_remove:
            break

        for key in keys_to_remove:
            inp.remove(key)

    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2025 day 4")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2025/day4/data/input.txt",
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
    "input1, output1", [("year2025/day4/data/test_input0.txt", 13)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2025/day4/data/test_input0.txt", 43)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
