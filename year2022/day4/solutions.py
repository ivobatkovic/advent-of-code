#!/usr/bin/env python3
import argparse
import pytest
import time
import re


def transform_input(input_):
    sections = []
    for row in input_.splitlines():
        l1, r1, l2, r2 = list(map(int, re.findall("\\d+", row)))
        left, right = set(range(l1, r1 + 1)), set(range(l2, r2 + 1))
        sections.append(
            [left, right] if len(left) < len(right) else [right, left]
        ),
    return sections


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)
    total = 0

    for small_set, big_set in inp:
        intersection = small_set.intersection(big_set)
        if len(intersection) == len(small_set):
            total += 1
    return total


def solve_part2(input_):
    inp = transform_input(input_)
    total = 0

    for small_set, big_set in inp:
        intersection = small_set.intersection(big_set)
        if len(intersection):
            total += 1
    return total


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2022 day 4")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2022/day4/data/input.txt",
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
    "input1, output1", [("year2022/day4/data/test_input0.txt", 2)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2022/day4/data/test_input0.txt", 4)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
