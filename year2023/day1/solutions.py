#!/usr/bin/env python3
import argparse
import re
import pytest
import time

mapping = {
    "one": "1",
    "1": "1",
    "two": "2",
    "2": "2",
    "three": "3",
    "3": "3",
    "four": "4",
    "4": "4",
    "five": "5",
    "5": "5",
    "six": "6",
    "6": "6",
    "seven": "7",
    "7": "7",
    "eight": "8",
    "8": "8",
    "nine": "9",
    "9": "9",
}


def transform_input(input_, digits=False):
    outputs = []
    if digits:
        regex = re.compile(
            r"(?=(one|two|three|four|five|six|seven|eight|nine|\d))"
        )
    else:
        regex = re.compile("\\d")
    for line in input_.splitlines():
        digits = regex.findall(line)
        outputs.append(int("".join([mapping[digits[0]], mapping[digits[-1]]])))
    return outputs


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def solve_part1(input_):
    inp = transform_input(input_)
    return sum(inp)


def solve_part2(input_):
    inp = transform_input(input_, digits=True)
    return sum(inp)


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2023 day 1")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2023/day1/data/input.txt",
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
    "input1, output1", [("year2023/day1/data/test_input0.txt", 142)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2023/day1/data/test_input1.txt", 281)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
