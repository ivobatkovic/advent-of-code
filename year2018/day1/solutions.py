#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    return [int(x) for x in input_.splitlines()]


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)
    return sum(inp)


def solve_part2(input_):
    inp = transform_input(input_)

    visited = set()
    frequency = 0

    while True:
        for f in inp:
            if frequency in visited:
                return frequency
            visited.add(frequency)
            frequency += f
    return 0


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2018 day 1")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2018/day1/data/input.txt",
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
    "input1, output1",
    [
        ("year2018/day1/data/test_input0.txt", 3),
        ("year2018/day1/data/test_input1.txt", 0),
        ("year2018/day1/data/test_input2.txt", -6),
    ],
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2018/day1/data/test_input3.txt", 10)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
