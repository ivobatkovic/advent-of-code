#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    return input_.splitlines()


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def find_marker(msg, length=4):
    for i in range(len(msg) - length):
        if len(set(msg[i : i + length])) == length:
            return i + length
    return 0


def solve_part1(input_):
    inp = transform_input(input_)
    return sum([find_marker(msg) for msg in inp])


def solve_part2(input_):
    inp = transform_input(input_)
    return sum([find_marker(msg, length=14) for msg in inp])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 6")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day6/data/input.txt",
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
    [("year2022/day6/data/test_input0.txt", 7 + 5 + 6 + 10 + 11)],
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2",
    [("year2022/day6/data/test_input0.txt", 19 + 23 + 23 + 29 + 26)],
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
