#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):

    output = []
    regex = re.compile("\\d+")
    for line in input_.splitlines():
        start, stop = regex.findall(line)
        output.append(([int(x) for x in start], [int(x) for x in stop]))
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def make_monotonic(num):
    for i in range(len(num) - 1):
        if num[i] > num[i + 1]:
            for j in range(i + 1, len(num)):
                num[j] = num[i]
            return num
    return num


def next_monotonic(digits):

    for i in range(len(digits) - 1, -1, -1):
        if digits[i] < 9:
            digits[i] += 1

            for j in range(i, len(digits)):
                digits[j] = digits[i]
            return digits
    return digits


def is_double_digit(digits, part_two=False):

    for i in range(0, len(digits) - 1):
        if digits[i] == digits[i + 1]:
            if not part_two:
                return True
            if i == 0 and digits[i + 1] != digits[i + 2]:
                return True
            elif i == len(digits) - 2 and digits[i - 1] != digits[i]:
                return True
            elif digits[i - 1] != digits[i] and digits[i + 1] != digits[i + 2]:
                return True
    return False


def solve_part1(input_):
    inp = transform_input(input_)

    output = 0
    for start, stop in inp:
        start = make_monotonic(start)
        while start <= stop:
            output += is_double_digit(start)
            start = next_monotonic(start)
    return output


def solve_part2(input_):
    inp = transform_input(input_)

    output = 0
    for start, stop in inp:
        start = make_monotonic(start)
        while start <= stop:
            output += is_double_digit(start, part_two=True)
            start = next_monotonic(start)
    return output


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2019 day 4")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2019/day4/data/input.txt",
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
    "input1, output1", [("year2019/day4/data/test_input0.txt", 1)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2019/day4/data/test_input1.txt", 2)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
