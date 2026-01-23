#!/usr/bin/env python3
import argparse
import math
import re
import pytest
import time


def transform_input(input_):
    lines = input_.splitlines()

    regex = re.compile(r"[*+]\s*")
    ops = regex.findall(lines[-1])

    numbers = []

    col = 0
    for op in ops:
        numbers_in_col = []
        for row in lines[:-1]:
            numbers_in_col.append(row[col : col + len(op)])
        numbers.append(numbers_in_col)
        col += len(op)

    return numbers, ops


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def get_numbers_from_column(col, numbers, part_two=False):

    if part_two:
        output = []
        for i in range(len(numbers[col][0])):
            digits = "".join(
                [char[i] for char in numbers[col] if char[i] != " "]
            )
            if digits:
                output.append(int(digits))
        return output

    return list(map(int, [x.strip() for x in numbers[col]]))


def solve_part1(input_):
    numbers, ops = transform_input(input_)

    output = 0
    for col in range(len(ops)):
        nums = get_numbers_from_column(col, numbers)
        output += math.prod(nums) if ops[col][0] == "*" else sum(nums)
    return output


def solve_part2(input_):
    numbers, ops = transform_input(input_)

    output = 0
    for col in range(len(ops)):
        nums = get_numbers_from_column(col, numbers, True)
        output += math.prod(nums) if ops[col][0] == "*" else sum(nums)

    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2025 day 6")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2025/day6/data/input.txt",
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
    "input1, output1", [("year2025/day6/data/test_input0.txt", 4277556)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2025/day6/data/test_input0.txt", 3263827)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
