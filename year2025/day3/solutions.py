#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    output = []
    for line in input_.splitlines():
        output.append([int(x) for x in line])
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def find_joltage(digits, length=2):
    N = len(digits)

    jolt = ""
    pos = 0

    look_ahead = N - length
    for _ in range(length):
        max_index, max_value = max(
            enumerate(digits[pos : pos + look_ahead + 1]), key=lambda x: x[1]
        )
        jolt += str(max_value)
        look_ahead -= max_index
        pos += max_index + 1
    return int(jolt)


def solve_part1(input_):
    inp = transform_input(input_)

    return sum([find_joltage(digits) for digits in inp])


def solve_part2(input_):
    inp = transform_input(input_)

    return sum([find_joltage(digits, length=12) for digits in inp])


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2025 day 3")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2025/day3/data/input.txt",
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
    "input1, output1", [("year2025/day3/data/test_input0.txt", 357)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2025/day3/data/test_input0.txt", 3121910778619)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
