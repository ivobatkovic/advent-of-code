#!/usr/bin/env python3
import argparse
import pytest
import time

from collections import defaultdict


def transform_input(input_):
    return input_.splitlines()


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def decode(lines, most_common=True):
    output = ""
    for col in zip(*lines):
        frequency = defaultdict(int)
        for char in col:
            frequency[char] += 1

        if most_common:
            output += max(frequency, key=frequency.get)
        else:
            output += min(frequency, key=frequency.get)

    return output


def solve_part1(input_):
    inp = transform_input(input_)

    return decode(inp)


def solve_part2(input_):
    inp = transform_input(input_)

    return decode(inp, most_common=False)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2016 day 6")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2016/day6/data/input.txt",
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
    "input1, output1", [("year2016/day6/data/test_input0.txt", "easter")]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2016/day6/data/test_input0.txt", "advent")]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
