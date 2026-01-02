#!/usr/bin/env python3
import argparse
import pytest
import time


def transform_input(input_):
    output = []
    for id_ranges in input_.split(","):
        ids = id_ranges.split("-")
        output.append([int(x) for x in ids])
    return output


def read_input(file_name):
    with open(file_name, "r") as f:
        return f.read()


def is_invalid(x, check_repeating=False):

    digits = []
    while x > 0:
        digits.append(x % 10)
        x //= 10

    if not check_repeating and len(digits) % 2 == 1:
        return False

    N = len(digits)

    T = 0 if check_repeating else N // 2
    for i in range(N // 2, T, -1):
        x_ = digits[0:i] * (N // i)
        if x_ == digits:
            return True

    return digits[: len(digits) // 2] == digits[len(digits) // 2 :]


def solve_part1(input_):
    inp = transform_input(input_)

    return sum(
        [
            num
            for id0, id1 in inp
            for num in range(id0, id1 + 1)
            if is_invalid(num)
        ]
    )


def solve_part2(input_):
    inp = transform_input(input_)

    return sum(
        [
            num
            for id0, id1 in inp
            for num in range(id0, id1 + 1)
            if is_invalid(num, check_repeating=True)
        ]
    )


def parse_args():
    parser = argparse.ArgumentParser(description="Solution to 2025 day 2")
    parser.add_argument(
        "file_name",
        type=str,
        default="year2025/day2/data/input.txt",
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
    "input1, output1", [("year2025/day2/data/test_input0.txt", 1227775554)]
)
def testPart1(input1, output1):
    assert solve_part1(read_input(input1)) == output1


@pytest.mark.parametrize(
    "input2, output2", [("year2025/day2/data/test_input0.txt", 4174379265)]
)
def testPart2(input2, output2):
    assert solve_part2(read_input(input2)) == output2
