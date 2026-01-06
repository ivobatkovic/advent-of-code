#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):
    regex = re.compile(r"mul\((\d+),(\d+)\)")
    output = []
    for line in input_.splitlines():
        for match in regex.findall(line):
            output.append([int(x) for x in match])
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)
    return sum([a * b for a, b in inp])


def transform_input_part_two(input_, enable=True):
    regex = re.compile(r"do\(\)|don't\(\)|mul\((\d+),(\d+)\)")

    output = []
    for line in input_.splitlines():
        for match in regex.finditer(line):
            if "don't(" in match.group():
                enable = False
            elif "do(" in match.group():
                enable = True
            elif enable:
                output.append([int(x) for x in match.groups()])
    return output


def solve_part2(input_):
    inp = transform_input_part_two(input_)
    return sum([a * b for a, b in inp])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2024 day 3")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2024/day3/data/input.txt",
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
    "input1, output1", [("year2024/day3/data/test_input0.txt", 161)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2024/day3/data/test_input1.txt", 48)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
