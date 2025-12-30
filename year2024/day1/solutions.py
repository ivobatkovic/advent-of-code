#!/usr/bin/env python3
import argparse
import pytest
import time

from collections import defaultdict


def transform_input(input_):
    L, R = [], []
    for line in input_.splitlines():
        nrs = line.split()
        L.append(int(nrs[0]))
        R.append(int(nrs[-1]))
    return L, R


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    L, R = transform_input(input_)
    return sum([abs(l - r) for l, r in zip(sorted(L), sorted(R))])


def solve_part2(input_):
    L, R = transform_input(input_)

    occurence = defaultdict(lambda: 0)
    for r in R:
        occurence[r] = occurence[r] + 1
    return sum([l * occurence[l] for l in L])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2024 day 1")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2024/day1/data/input.txt",
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
    "input1, output1", [("year2024/day1/data/test_input0.txt", 11)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2024/day1/data/test_input0.txt", 31)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
