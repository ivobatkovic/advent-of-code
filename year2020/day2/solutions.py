#!/usr/bin/env python3
import argparse
import re
import pytest
import time


def transform_input(input_):

    re_digits = re.compile("(\\d+)-(\\d+)")
    re_letter = re.compile("([a-z]):")
    re_password = re.compile(": (\\w+)")

    outputs = []
    for line in input_.splitlines():
        low, hi = re_digits.findall(line)[0]
        letter = re_letter.findall(line)[0]
        password = re_password.findall(line)[0]
        outputs.append([int(low), int(hi), letter, password])
    return outputs


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)
    return sum(
        [
            1
            for low, hi, letter, password in inp
            if low <= password.count(letter) <= hi
        ]
    )


def solve_part2(input_):
    inp = transform_input(input_)
    return sum(
        [
            1
            for low, hi, letter, password in inp
            if (password[low - 1] == letter) ^ (password[hi - 1] == letter)
        ]
    )


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2020 day 2")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2020/day2/data/input.txt",
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
    "input1, output1", [("year2020/day2/data/test_input0.txt", 2)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2020/day2/data/test_input0.txt", 1)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
